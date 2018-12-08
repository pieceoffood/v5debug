#pragma once
#include "../userDisplay/userDisplay.hpp"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MAX_BUF_LEN 1024
#define MAX_KEY_LEN 64
#define MAX_VAL_LEN 256
class Config
{
  private:
    std::vector<std::pair<std::string, std::string>> _data;
    typedef std::vector<std::pair<std::string, std::string>>::const_iterator iter;
    bool _changeFlag = false;
    bool _openFlag = false;
    std::string _filePath;
    void Trim(char s[])
    {
        for (int n = strlen(s) - 1; n >= 0; n--)
        {
            if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
                break;
            s[n + 1] = '\0';
        }
    }

  public:
    Config(const std::string &filePath) : _filePath(filePath)
    {
        FILE *file = fopen(_filePath.c_str(), "r");
        if (file == NULL)
        {
            std::cerr << "file open error" << std::endl;
            _openFlag = false;
        }
        else
        {
            char buf[MAX_BUF_LEN];
            int text_comment = 0;
            while (fgets(buf, MAX_BUF_LEN, file) != NULL)
            {

                Trim(buf);
                // to skip text comment with flags /* ... */
                if (buf[0] != '#' && (buf[0] != '/' || buf[1] != '/'))
                {
                    if (strstr(buf, "/*") != NULL)
                    {
                        text_comment = 1;
                        continue;
                    }
                    else if (strstr(buf, "*/") != NULL)
                    {
                        text_comment = 0;
                        continue;
                    }
                }
                if (text_comment == 1)
                {
                    continue;
                }

                int buf_len = strlen(buf);
                // ignore and skip the line with first chracter '#', '=' or '/'
                if (buf_len <= 1 || buf[0] == '#' || buf[0] == '=' || buf[0] == '/')
                {
                    continue;
                }
                buf[buf_len - 1] = '\0';

                char _paramk[MAX_KEY_LEN] = {0}, _paramv[MAX_VAL_LEN] = {0};
                int _kv = 0, _klen = 0, _vlen = 0;
                int i = 0;
                for (i = 0; i < buf_len; ++i)
                {
                    if (buf[i] == ' ')
                        continue;
                    // scan param key name
                    if (_kv == 0 && buf[i] != '=')
                    {
                        if (_klen >= MAX_KEY_LEN)
                            break;
                        _paramk[_klen++] = buf[i];
                        continue;
                    }
                    else if (buf[i] == '=')
                    {
                        _kv = 1;
                        continue;
                    }
                    // scan param key value
                    if (_vlen >= MAX_VAL_LEN || buf[i] == '#')
                        break;
                    _paramv[_vlen++] = buf[i];
                }
                if (strcmp(_paramk, "") == 0 || strcmp(_paramv, "") == 0)
                    continue;
                _data.push_back(std::make_pair(_paramk, _paramv));
            }
            fclose(file);
            _openFlag = true;
        }
    }
    /**
     * 遍历显示CONFIG
     */
    void showConfig()
    {
        for (auto &it : _data)
            userDisplay->ostr << it.first << "=" << it.second << std::endl;
    }
    /**
     * 查找函数
     * @param  key 关键字
     * @return     返回迭代器(在VECTOR中的位置 没找到返回END())
     */
    iter find(std::string key)
    {
        iter it = _data.begin();
        for (; it != _data.end(); it++)
        {
            if (it->first == key)
                return it;
        }
        return _data.end();
    }

    /**
     * 按KEY查找CONFIG的值
     * @param  key 关键字
     * @return     关键字对应的值
     */
    template <class T>
    T read(std::string key)
    {
        iter it = find(key);
        if (it == _data.end())
            std::cerr << "Key not found" << std::endl;
        else
            return stringToNum<T>(it->second);
    }
    /**
     * 修改config的值
     * @param  key   关键字
     * @param  value 关键字对应的值
     * @return        修改成功返回true 失败返回false
     */
    bool setConfig(std::string key, std::string value)
    {
        if (_openFlag == false)
            return false;
        _changeFlag = true;
        for (auto &it : _data)
            if (it.first == key)
            {
                it.second = value; //如果找到了就修改
                return true;
            }
        _data.push_back(std::pair<std::string, std::string>(key, value)); //如果没找到就新增

        return true;
    }
    /**
     * 遍历保存config
     * @return 成功返回true 失败返回false
     */
    bool saveConfig()
    {
        if (_openFlag == false)
        {
            std::cerr << "file open error" << std::endl;
            return false;
        }
        if (_changeFlag == false)
            return true;

        FILE *file = fopen(_filePath.c_str(), "w");
        if (file == NULL)
        {
            std::cerr << "file open error" << std::endl;
            return false;
        }
        for (auto &it : _data)
        {
            fprintf(file, "%s = %s\n", it.first.c_str(), it.second.c_str());
        }
        fclose(file);
        _changeFlag = false;
        return true;
    }
    template <class T>
    static T stringToNum(const std::string &str);

    // template <class T>
    // static std::string T_as_string(const T &t);
    // template <class T>
    // static T string_as_T(const std::string &s);
};
template <class T>
T Config::stringToNum(const std::string &str)
{
    std::istringstream iss(str);
    T num;
    iss >> num;
    return num;
}
extern Config *config;
//
// /* static */
// template <class T>
// std::string Config::T_as_string(const T &t)
// {
//     // Convert from a T to a string
//     // Type T must support << operator
//     std::ostringstream ost;
//     ost << t;
//     return ost.str();
// }
//
// /* static */
// template <class T>
// T Config::string_as_T(const std::string &s)
// {
//     // Convert from a string to a T
//     // Type T must support >> operator
//     T t;
//     std::istringstream ist(s);
//     ist >> t;
//     return t;
// }
//
// /* static */
// template <>
// inline std::string Config::string_as_T<std::string>(const std::string &s)
// {
//     // Convert from a string to a string
//     // In other words, do nothing
//     return s;
// }
//
// /* static */
// template <>
// inline bool Config::string_as_T<bool>(const std::string &s)
// {
//     // Convert from a string to a bool
//     // Interpret "false", "F", "no", "n", "0" as false
//     // Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true
//     bool b = true;
//     std::string sup = s;
//     for (std::string::iterator p = sup.begin(); p != sup.end(); ++p)
//         *p = toupper(*p); // make string all caps
//     if (sup == std::string("FALSE") || sup == std::string("F") ||
//         sup == std::string("NO") || sup == std::string("N") ||
//         sup == std::string("0") || sup == std::string("NONE"))
//         b = false;
//     return b;
// }

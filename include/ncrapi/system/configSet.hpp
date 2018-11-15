#ifndef CONFIGSET_HPP_
#define CONFIGSET_HPP_

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
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
        FILE *file = fopen(_filePath.c_str(), "r+");
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
            std::cout << it.first << "=" << it.second << std::endl;
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
    std::string getConfig(std::string key)
    {
        iter it = find(key);
        if (it == _data.end())
        {
            std::cerr << "Key not found" << std::endl;
            return "";
        }
        else
            return it->second;
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

        FILE *file = fopen(_filePath.c_str(), "w+");
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
};
#endif /* end of include guard: CONFIGSET_HPP_ */

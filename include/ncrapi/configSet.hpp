#ifndef CONFIGSET_HPP_
#define CONFIGSET_HPP_

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class Config
{
  protected:
    std::string m_Delimiter;                       //！<键和值之间的分隔符
    std::string m_Comment;                         //！<值和注释之间的分隔符
    std::map<std::string, std::string> m_Contents; //用于临时存贮的map类

    typedef std::map<std::string, std::string>::iterator mapi;
    typedef std::map<std::string, std::string>::const_iterator mapci;
    // 方法
  public:
    Config(std::string filename, std::string delimiter = "=", std::string comment = "#");
    Config();
    /**
     * 读取KEY后面对应的值 用法configTest.Read<int>("chs_LF")
     * @param  key 关键字
     * @return     KEY对应的值
     */
    template <class T>
    T read(const std::string &key) const //！<搜索键和读取值或可选的默认值，调用read <T>
    {
        // 读取与key对应的值
        mapci p = m_Contents.find(key);
        if (p == m_Contents.end()) throw Key_not_found(key);
        return string_as_T<T>(p->second);
    }
    /**
     * 返回与key或给定默认值对应的值,如果找不到则返回参数2
     * @param  key   关键字
     * @param  value 如果找不到关键字 则返回这个数字
     * @return     返回value
     */
    template <class T>
    T read(const std::string &key, const T &value) const
    {
        //如果找不到密钥
        mapci p = m_Contents.find(key);
        if (p == m_Contents.end())
            return value;
        return string_as_T<T>(p->second);
    }
    /**
     * 获取与key对应的值并存储在var中
     * @param  var 用来保存值的变量
     * @param  key 关键字
     * @return     如果找到密钥，则返回true 否则返回0 并保持var不变
     */
    template <class T>
    bool readInto(T &var, const std::string &key) const
    {

        mapci p = m_Contents.find(key);
        bool found = (p != m_Contents.end());
        if (found)
            var = string_as_T<T>(p->second);
        return found;
    }
    /**
     * 获取与key对应的值并存储在var中
     * @param  var  用来保存值的变量
     * @param  key   关键字
     * @param  value 如果找不到关键字 则返回这个数字
     * @return      如果找到密钥，则返回true 否则返回0 并将var设置为给定的默认值
     */
    template <class T>
    bool readInto(T &var, const std::string &key, const T &value) const
    {

        mapci p = m_Contents.find(key);
        bool found = (p != m_Contents.end());
        if (found)
            var = string_as_T<T>(p->second);
        else
            var = value;
        return found;
    }
    /**
     * 判断文件是否存在
     * @param  filename 文件路径和名字
     * @return          如果文件存在返回1 不存在返回0
     */
    bool fileExist(std::string filename);
    /**
     * 读取config文件
     * @param filename  config路径
     * @param delimiter KEY和VALUE的分隔符
     * @param comment   注释的分隔符
     */
    void readFile(std::string filename, std::string delimiter = "=", std::string comment = "#");

    /**
     * 检查文件中是否存在对应关键字
     * @param  key 对应的项目 如robotStyle
     * @return     找到返回1 没找到返回0
     */
    bool keyExists(const std::string &in_key) const;

    /**
 * 添加具有给定值的关键字到内存中(注意是内存不是文件中)
 * @param in_key 关键字的名字
 * @param value  值
 */
    template <class T>
    void add(const std::string &in_key, const T &value)
    {

        std::string v = T_as_string(value);
        std::string key = in_key;
        Trim(key);
        Trim(v);
        m_Contents[key] = v;
        return;
    }
    /**
     * 从内存中删除键及其值(注意是内存不是文件中)
     *警告:有BUG 如果输错名字 就全部删了...
     * @param key 关键字
     */
    void remove(const std::string &key);
    /**
     * 获取分隔符标志
     * @return 返回分隔符标志
     */
    std::string getDelimiter() const { return m_Delimiter; }
    /**
     * 获取注释标志
     * @return 返回注释标志
     */
    std::string getComment() const { return m_Comment; }
    /**
     * 重新设置分隔符
     * @param  in_s 新的分隔符
     * @return      返回老的分隔符
     */
    std::string SetDelimiter(const std::string &in_s)
    {
        std::string old = m_Delimiter;
        m_Delimiter = in_s;
        return old;
    }
    /**
     * 重新设置注释符
     * @param  in_s 新的注释符
     * @return      返回老的注释符
     */
    std::string SetComment(const std::string &in_s)
    {
        std::string old = m_Comment;
        m_Comment = in_s;
        return old;
    }
    void showConfig()
    {
        for (auto &it : m_Contents)
        {
            std::cout << it.first << "=" << it.second << std::endl;
        }
    }

    /**
     * 输出或者将配置保存到操作系统
     * 用法
     * freopen("../t2.txt", "w", stdout); //重定向 "w" 写重定向
     * std::cout << configTest << std::endl;
     */
    friend std::ostream &operator<<(std::ostream &os, const Config &cf);
    /**
     * 读取文件
     */
    friend std::istream &operator>>(std::istream &is, Config &cf);

  protected:
    template <class T>
    static std::string T_as_string(const T &t);
    template <class T>
    static T string_as_T(const std::string &s);
    static void Trim(std::string &inout_s);

    //异常类型
  public:
    struct File_not_found
    {
        std::string filename;
        File_not_found(const std::string &filename_ = std::string())
            : filename(filename_) {}
    };
    struct Key_not_found
    { //仅由read（）的T read（key）变量抛出
        std::string key;
        Key_not_found(const std::string &key_ = std::string())
            : key(key_) {}
    };
};

/* static */
template <class T>
std::string Config::T_as_string(const T &t)
{
    // Convert from a T to a string
    // Type T must support << operator
    std::ostringstream ost;
    ost << t;
    return ost.str();
}

/* static */
template <class T>
T Config::string_as_T(const std::string &s)
{
    // Convert from a string to a T
    // Type T must support >> operator
    T t;
    std::istringstream ist(s);
    ist >> t;
    return t;
}

/* static */
template <>
inline std::string Config::string_as_T<std::string>(const std::string &s)
{
    // Convert from a string to a string
    // In other words, do nothing
    return s;
}

/* static */
template <>
inline bool Config::string_as_T<bool>(const std::string &s)
{
    // Convert from a string to a bool
    // Interpret "false", "F", "no", "n", "0" as false
    // Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true
    bool b = true;
    std::string sup = s;
    for (std::string::iterator p = sup.begin(); p != sup.end(); ++p)
        *p = toupper(*p); // make string all caps
    if (sup == std::string("FALSE") || sup == std::string("F") ||
        sup == std::string("NO") || sup == std::string("N") ||
        sup == std::string("0") || sup == std::string("NONE"))
        b = false;
    return b;
}
#endif /* end of include guard: CONFIGSET_HPP_ */

/**
 * @Author: 陈昱安
 * @Date:   2018-09-24T21:24:20+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T21:54:43+08:00
 */

#ifndef _PROS_API_EXTENDED_H_
#define _PROS_API_EXTENDED_H_

#include "api.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include "display/lvgl.h"
#pragma GCC diagnostic pop

#ifdef __cplusplus
extern "C"
{
    using namespace pros;
#endif

    /******************************************************************************/
    /**                             RTOS 的库函数                                 **/
    /**                                                                          **/
    /**                                                                          **/
    /**打开 https://pros.cs.purdue.edu/v5/extended/multitasking.html 以便更多的学习**/
    /******************************************************************************/

    typedef void *queue_t;
    typedef void *sem_t;

    /**
* 解锁阻止状态的任务（例如，等待延迟，信号量等）
* @param  task 任务的句柄
* @return      [description]
*/

    bool task_abort_delay(task_t task);

    /**
* 创建一个递归互斥锁，可以由所有者递归锁定。
* @return  新创建的递归互斥锁。
*/
    mutex_t mutex_recursive_create(void);
    /**
* 采用递归互斥量。
* @param  mutex   要使用的互斥量。
* @param  timeout 在互斥锁可用之前等待的时间。超时0可用于轮询互斥锁。TIMEOUT_MAX可用于无限期阻止。
* @return         如果获得互斥锁，则返回 1，否则返回 0
*/
    bool mutex_recursive_take(mutex_t mutex, uint32_t timeout);

    /**
* 给出一个递归的互斥量。
* @param  mutex 要解锁的互斥锁
* @return       [description]
*/
    bool mutex_recursive_give(mutex_t mutex);

    /**
* 返回互斥锁所有者的句柄。
* @param  mutex 要检查的互斥锁
* @return       [description]
*/
    task_t mutex_get_owner(mutex_t mutex);

    /**
* 创建计数信号量。
* @param  max_count  可以达到的最大计数值
* @param  init_count 分配给新信号量的初始计数值
* @return            新创建的信号量。如果发生错误，将返回NULL并errno可以检查有关sem_create失败原因的提示。
*/
    sem_t sem_create(uint32_t max_count, uint32_t init_count);
    /**
* 删除计数信号量
* @param sem 要删除的对象
*/
    void sem_delete(sem_t sem);

    /**
*  创建二进制信号量。
* @return  新创建的信号量。
*/
    sem_t sem_binary_create(void);

    /**
* 等待信号量的值大于0.如果该值大于0，则此函数立即返回。
* @param  sem     要等待的信号量。
* @param  timeout 在信号量可用之前等待的时间。超时0可用于轮询信号量。TIMEOUT_MAX可用于无限期阻止。
* @return         返回：如果成功获取信号量，则返回 true，否则返回 false。如果返回false，则设置errno，提示为什么不能采取sempahore。
*/
    bool sem_wait(sem_t sem, uint32_t timeout);
    /**
* 增加信号量的值。
* @param  sem 	要发布的信号量。
* @return     返回：如果值增加，则返回 true，否则返回 false。如果返回false，则errno设置一个提示，说明无法获取信号量的原因。
*/
    bool sem_post(sem_t sem);
    /**
* 返回信号量的当前值。
* @param  sem 要检查的信号量
* @return     返回：信号量的当前值（例如，可用资源的数量）
*/
    uint32_t sem_get_count(sem_t sem);

    /**
* 创建一个队列。
* @param  length    队列可以包含的最大项目数。
* @param  item_size 	队列中每个项目所需的字节数。
* @return           新创建的队列的句柄，如果无法创建队列，则返回 NULL。
*/
    queue_t queue_create(uint32_t length, uint32_t item_size);
    /**
* 将项目发布到队列的前面。该项目按副本排队，而不是按引用排队。
* @param  queue   队列句柄
* @param  item    指向将放置在队列中的项的指针。
* @param  timeout 	是时候等待空间变得可用了。超时为0可用于尝试发布而不阻塞。TIMEOUT_MAX可用于无限期阻止。
* @return         true如果项目已预先生成，false则返回。
*/
    bool queue_prepend(queue_t queue, const void *item, uint32_t timeout);
    /**
* 将项目发布到队列末尾。该项目按副本排队，而不是按引用排队
* @param  queue   	队列句柄
* @param  item    指向将放置在队列中的项的指针。
* @param  timeout 是时候等待空间变得可用了。超时为0可用于尝试发布而不阻塞。TIMEOUT_MAX可用于无限期阻止。
* @return          true如果项目已预先生成，false则返回。
*/
    bool queue_append(queue_t queue, const void *item, uint32_t timeout);

    /**
* 从队列中接收项目而不从队列中删除项目。
* @param  queue   队列句柄
* @param  buffer  指向要将所接收项目复制到的缓冲区的指针
* @param  timeout 是时候等待空间变得可用了。超时为0可用于尝试发布而不阻塞。TIMEOUT_MAX可用于无限期阻止。
* @return         true如果项目已复制到缓冲区中，false否则返回。
*/
    bool queue_peek(queue_t queue, void *const buffer, uint32_t timeout);

    /**
* 从队列中接收项目。
* @param  queue   队列句柄
* @param  buffer  指向要将所接收项目复制到的缓冲区的指针
* @param  timeout 是时候等待空间变得可用了。超时为0可用于尝试发布而不阻塞。TIMEOUT_MAX可用于无限期阻止。
* @return         true如果项目已复制到缓冲区中，false否则返回。
*/
    bool queue_recv(queue_t queue, void *const buffer, uint32_t timeout);

    /**
* 返回存储在队列中的消息数
* @param  queue 队列句柄
* @return       队列中可用消息的数量。
*/
    uint32_t queue_get_waiting(const queue_t queue);

    /**
* 返回队列中剩余的空格数。
* @param  queue 队列句柄
* @return       队列中剩余的空格数。
*/
    uint32_t queue_get_available(const queue_t queue);

    /**
* 删除队列。
* @param queue 要删除的队列句柄
*/
    void queue_delete(queue_t queue);

    /**
* 将队列重置为空状态。
* @param queue 要重置的队列句柄
*/
    void queue_reset(queue_t queue);

    /******************************************************************************/
    /**                           Device Registration                            **/
    /******************************************************************************/

    /*
*表示正在与之通信的设备类型。
*/
    typedef enum v5_device_e
    {
        E_DEVICE_NONE = 0,
        E_DEVICE_MOTOR = 2,
        E_DEVICE_RADIO = 8,
        E_DEVICE_VISION = 11,
        E_DEVICE_ADI = 12,
        E_DEVICE_GENERIC = 129,
        E_DEVICE_UNDEFINED = 255
    } v5_device_e_t;

    /**
* 如果检测到该类型的设备插入该端口，则将给定端口中给定类型的设备注册到注册表中。
* @param  port        	注册设备的端口号
* @param  device_type 要注册的设备类型
* @return             成功时返回 1，失败时返回 PROS_ERR
*/
    int registry_bind_port(uint8_t port, v5_device_e_t device_type);

    /**
* 删除给定端口中注册的设备（如果有）。
* @param  port 取消注册的端口号
* @return      成功时返回 1，失败时返回 PROS_ERR
*/
    int registry_unbind_port(uint8_t port);

    /******************************************************************************/
    /**                               文件系统                                 **/
    /******************************************************************************/
    /**
* 控制串行驱动程序的设置。
* @param  action    要对串行驱动程序执行的操作。有关不同操作的详细信息，请参阅SERCTL_ *宏。
* @param  extra_arg 根据操作传入的参数。
* @return           [description]
*/
    int32_t serctl(const uint32_t action, void *const extra_arg);
    /**
* 控制文件驱动程序处理文件的方式的设置。
* @param  file      有效的文件描述符编号
* @param  action    要对文件驱动程序执行的操作。有关不同操作的详细信息，
* 请参阅CTL_宏。请注意，传入的操作必须与正确的驱动程序匹配（例如，不要对microSD卡文件执行SERCTL_ *操作）。
* @param  extra_arg 	根据操作传入的参数。
* @return           [description]
*/
    int32_t fdctl(int file, const uint32_t action, void *const extra_arg);

/**
*
*/
#define SERCTL_ACTIVATE 10 //Action宏传递到激活流标识符的serctl或fdctl。当与serctl一起使用时，额外参数必须是流标识符的小端表示（例如“sout” - > 0x74756f73）

#define SERCTL_DEACTIVATE 11 //要传递给停用流标识符的serctl或fdctl的 Action宏。当与serctl一起使用时，额外参数必须是流标识符的小端表示（例如“sout” - > 0x74756f73）

#define SERCTL_BLKWRITE 12 //要传递到fdctl的 Action宏，它允许阻止对文件的写入。额外参数不与此操作一起使用，而是提供任何值（例如NULL）。

#define SERCTL_NOBLKWRITE 13 //动作宏传递到fdctl，使文件的写入无阻.动作宏传递到fdctl，使文件的写入无阻

#define SERCTL_ENABLE_COBS 14 //Action宏传递到serctl，启用高级流复用功能。额外参数不与此操作一起使用，而是提供任何值（例如NULL）。

#define SERCTL_DISABLE_COBS 15 //Action宏传递到serctl，禁用高级流复用功能。额外参数不与此操作一起使用，而是提供任何值（例如NULL）。

#define DEVCTL_FIONREAD 16 //动作宏，用于检查通用串行设备是否有可用数据。额外参数不与此操作一起使用，而是提供任何值（例如NULL）。

#define DEVCTL_SET_BAUDRATE 17 //动作宏以设置通用串行设备的波特率。动作宏以设置通用串行设备的波特率

#ifdef __cplusplus
}
#endif

#endif // _PROS_API_EXTENDED_H_

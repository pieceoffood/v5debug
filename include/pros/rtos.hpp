#ifndef _PROS_RTOS_HPP_
#define _PROS_RTOS_HPP_

#include "pros/rtos.h"
#undef delay
#include <cstdint>
#include <cstdlib>

namespace pros
{
class Task
{
  public:
    /**
  	 *创建新任务并将其添加到准备运行的任务列表中。
  	 *
  	 *当错误状态为时，此函数使用以下errno值
  	 * 到达：
  	 * ENOMEM  - 由于未创建TCB，因此无法使用堆栈。
  	 *
  	 * \ param函数 指向任务输入功能的指针
  	 * \ param参数 指向将用作任务参数的内存的指针 正在创建。这个内存通常不应来自堆栈 而是动态地（即malloc'd）或静态地分配内存。
  	 * \ param prio 任务运行的优先级。通常使用TASK_PRIO_DEFAULT加/减1或2。
  	 * \ param stack_depth 任务中可用的单词数（即4 * stack_depth） 堆栈。TASK_STACK_DEPTH_DEFAULT通常是足够的。
  	 * \ param名称 任务的描述性名称。这主要是为了方便调试。名称最长可达32个字符。
  	 */
    Task(task_fn_t function, void *parameters = NULL, std::uint32_t prio = TASK_PRIORITY_DEFAULT,
         std::uint16_t stack_depth = TASK_STACK_DEPTH_DEFAULT, const char *name = "");
    /**
	*创建新任务并将其添加到准备运行的任务列表中。
	* \ param任务
	* task_create（）的任务句柄，用于创建pros :: Task
	*对象。
	 */
    Task(task_t task);

    /**
	*创建新任务并将其添加到准备运行的任务列表中。
   	 *
   	 * \ param in
   	 * task_create（）的任务句柄，用于创建pros :: Task
   	 *对象。
	 */
    void operator=(const task_t in);

    /**
	*从RTOS实时内核的管理中删除任务。这个任务
	*将从所有就绪，阻止，暂停和事件列表中删除。
	*
	*任务动态分配的内存不会自动释放，并且
	*应在删除任务之前释放。
	 */
    void remove();

    /**
	*获取指定任务的优先级。
	*
	* \ return任务的优先级
	 */
    std::uint32_t get_priority(void);

    /**
	*设置指定任务的优先级。
	*
	*如果可以安排指定任务的状态（例如，没有
	*已阻止）并且新优先级高于当前正在运行的任务，
	*可能发生上下文切换。
	*
	* \ param prio
	*任务的新优先级
	 */
    void set_priority(std::uint32_t prio);

    /**
	*获取指定任务的状态。
	*
	* \ return任务的状态
	 */
    std::uint32_t get_state(void);

    /**
	 *暂停指定的任务，使其无法安排。
	 */
    void suspend(void);

    /**
	*恢复指定的任务，使其有资格安排。
	*
	* \ param任务
	*要恢复的任务
	 */
    void resume(void);

    /**
	*获取指定任务的名称。
	*
	* \ return指向任务名称的指针
	 */
    const char *get_name(void);

    /**

	 */
    std::uint32_t notify(void);

    /**
	*向任务发送通知，可选择执行某些操作。将
	*之前还检索目标任务中的通知值
	*修改通知值。
	*
	*请参阅https://pros.cs.purdue.edu/v5/tutorials/topical/notifications.html
	* 细节。
	*
	* \ param值
	*执行操作时使用的值
	* \ param行动
	*可选择执行接收任务通知的操作
	*价值
	* \ param prev_value
	*一个指针，用于存储目标任务的先前值
	*通知，可能为NULL
	*
	* \ return取决于通知操作。
	*对于NOTIFY_ACTION_NO_WRITE：如果值可以不写，则返回0
	*需要覆盖，否则为1。
	*对于所有其他NOTIFY_ACTION值：始终返回0
	 */
    std::uint32_t notify_ext(std::uint32_t value, notify_action_e_t action, std::uint32_t *prev_value);

    /**
	*等待通知非零。
	*
	*请参阅https://pros.cs.purdue.edu/v5/tutorials/topical/notifications.html
	* 细节。
	*
	* \ param clear_on_exit
	*如果为真（1），则清除通知值。
	*如果为false（0），则通知值递减。
	* \ param超时
	*指定等待通知所花费的时间
	* 发生。
	*
	* \ return任务的通知值在递减之前的值
	*或清除
	 */
    std::uint32_t notify_take(bool clear_on_exit, std::uint32_t timeout);

    /**
	*清除任务通知。
	*
	*请参阅https://pros.cs.purdue.edu/v5/tutorials/topical/notifications.html
	* 细节。
	*
	* \如果没有通知等待返回False，如果有，则返回true
	 */
    bool notify_clear(void);

    /**
	*将任务延迟给定的毫秒数。
	*
	*这不是让任务执行预定义代码的最佳方法
	*间隔，因为延迟时间是从请求延迟时开始计算的。
	*要循环延迟，请使用task_delay_until（）。
	*
	* \ param毫秒
	*等待的毫秒数（每秒1000毫秒）
	 */
    static void delay(const std::uint32_t milliseconds);

    /**
	*将任务延迟到指定时间。此功能可以使用
	*定期任务，以确保恒定的执行频率。
	*
	*任务将在* prev_time + delta和* prev_time时被唤醒
	*将更新以反映任务取消阻止的时间。
	*
	* \ param prev_time
	*指向存储设定点时间的位置的指针。这应该
	*通常初始化为pros :: millis（）的返回值。
	* \ param delta
	*等待的毫秒数（每秒1000毫秒）
	 */
    static void delay_until(std::uint32_t *const prev_time, const std::uint32_t delta);

    /**
	*获取内核当前管理的任务数，包括所有任务
	*准备，阻止或暂停任务。已删除的任务，但不是
	*由空闲任务收获但也将包含在计数中。
	*最近创建的任务可能需要计算一个上下文切换。
	*
	* \ return内核当前正在管理的任务数。
	 */
    static std::uint32_t get_count(void);

  private:
    task_t task;
};

class Mutex
{
  public:
    Mutex(void);

    /**
	*获取并锁定互斥锁，等待一定的毫秒数
	*超时之前。
	*
	*见
	* https://pros.cs.purdue.edu/v5/tutorials/topical/multitasking.html#mutexes
	*了解详情。
	*
	* \ param超时
	*在互斥锁可用之前等待的时间。超时为0即可
	*用于轮询互斥锁。TIMEOUT_MAX可用于阻止
	*无限期。
	*
	* \如果成功获取互斥锁，则返回True，否则返回false。如果是假的
	返回*，然后设置errno，提示有关互斥锁的原因
	*无法采取。
	 */
    bool take(std::uint32_t timeout);

    /**
	*解锁互斥锁。
	*
	*见
	* https://pros.cs.purdue.edu/v5/tutorials/topical/multitasking.html#mutexes
	*了解详情。
	*
	* \如果成功返回互斥锁，则返回True，否则返回false。如果
	*返回false，然后设置errno，提示有关互斥锁的原因
	*无法退回。
	 */
    bool give(void);

  private:
    mutex_t mutex;
};

/**
*获取自PROS初始化以来的毫秒数。
*
* \ return PROS初始化后的毫秒数
 */
using pros::c::millis;

/**
*将任务延迟给定的毫秒数。
*
*这不是让任务执行预定义代码的最佳方法
*间隔，因为延迟时间是从请求延迟时开始计算的。
*要循环延迟，请使用task_delay_until（）。
*
* \ param毫秒
*等待的毫秒数（每秒1000毫秒）
 */
using pros::c::delay;
} // namespace pros

#endif // _PROS_RTOS_HPP_s

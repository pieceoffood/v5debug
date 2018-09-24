/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T22:50:35+08:00
 */
#ifndef _PROS_RTOS_H_
#define _PROS_RTOS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
    namespace pros
    {
#endif

// 可以分配给任务的最高优先级。小心僵局。
#define TASK_PRIORITY_MAX 16

// 可分配给任务的最低优先级。这可能会导致严重的性能问题，通常不建议这样做。
#define TASK_PRIORITY_MIN 1

    //默认任务优先级，应该用于大多数任务。诸如autonomous（）之类的默认任务继承此优先级。
#define TASK_PRIORITY_DEFAULT 8

// 新任务的建议堆栈大小。此堆栈大小用于默认任务，例如autonomous（）。这相当于32,768字节，或PROS 2中任务的默认堆栈大小的128倍。
#define TASK_STACK_DEPTH_DEFAULT 0x2000

// 任务的最小堆栈大小。这相当于2048字节，或PROS 2中任务的默认堆栈大小的8倍。
#define TASK_STACK_DEPTH_MIN 0x200

// 任务名称中允许的最大字符数。
#define TASK_NAME_MAX_LEN 32

//可以赋予的最大超时值，例如，互斥锁抓取。
#define TIMEOUT_MAX ((uint32_t)0xffffffffUL)

    typedef void *task_t;
    typedef void (*task_fn_t)(void *);

    typedef enum
    {
        E_TASK_STATE_RUNNING = 0,
        E_TASK_STATE_READY,
        E_TASK_STATE_BLOCKED,
        E_TASK_STATE_SUSPENDED,
        E_TASK_STATE_DELETED,
        E_TASK_STATE_INVALID
    } task_state_e_t;

    typedef enum
    {
        E_NOTIFY_ACTION_NONE,
        E_NOTIFY_ACTION_BITS,
        E_NOTIFY_ACTION_INCR,
        E_NOTIFY_ACTION_OWRITE,
        E_NOTIFY_ACTION_NO_OWRITE
    } notify_action_e_t;

    typedef void *mutex_t;

//指当前的任务。用于检查调用此宏的任务的属性。
#define CURRENT_TASK ((task_t)NULL)

#ifdef __cplusplus
    namespace c
    {
#endif

    /**
 * 返回自PROS初始化以来的毫秒数。
 * @return  返回自PROS初始化以来的毫秒数。
 */
    uint32_t millis(void);

    /**
 * 创建一个新任务并将其添加到准备运行的任务列表中。
 * @param  function    	指向任务输入功能的指针
 * @param  parameters  指向内存的指针，用作正在创建的任务的参数。此内存通常不应来自堆栈，而应来自动态（即malloc'd）或静态分配的内存。
 * @param  prio        任务应该运行的优先级。通常使用TASK_PRIO_DEFAULT加/减1或2。
 * @param  stack_depth 任务堆栈上可用的单词数（即4 * stack_depth）。TASK_STACK_DEPTH_DEFAULT通常就足够了。
 * @param  name        	任务的描述性名称。这主要用于方便调试。名称最长可达32个字符。
 * @return             将返回一个句柄，通过该句柄可以引用新创建的任务。如果发生错误，将返回NULL并errno可以检查有关task_create失败原因的提示。
 */
    task_t task_create(task_fn_t function, void *const parameters, uint32_t prio, const uint16_t stack_depth,
                       const char *const name);

    /**
 * 从RTOS实时内核的管理中删除任务。正在删除的任务将从所有就绪，阻止，暂停和事件列表中删除。
 * 任务动态分配的内存不会自动释放，应在删除任务之前释放。
 * @param task 	要删除的任务的句柄。传递NULL将导致调用任务被删除。
 */
    void task_delete(task_t task);

    /**
 * 将任务延迟给定的毫秒数。这不是使任务以预定义的间隔执行代码的最佳方法，
 * 因为延迟时间是从请求延迟时开始测量的。要循环延迟，请使用task_delay_until。
 * @param milliseconds 	等待的毫秒数（每秒1000毫秒）
 */
    void task_delay(const uint32_t milliseconds);

    void delay(const uint32_t milliseconds);

    /**
 * 将任务延迟到指定时间。周期性任务可以使用此功能来确保恒定的执行频率。
 * 该任务将在当时被唤醒，并将更新以反映任务将解除阻止的时间。*prev_time + delta*prev_time
 * @param prev_time 指向存储设定点时间的位置的指针
 * @param delta     等待的毫秒数（每秒1000毫秒）
 */
    void task_delay_until(uint32_t *const prev_time, const uint32_t delta);

    /**
 * 获得指定任务的优先级。
 * @param  task 要检查的任务的句柄
 * @return      任务的优先级。
 */
    uint32_t task_get_priority(task_t task);

    /**
* 重新设置当前线程的优先级,如果指定任务的状态可用于调度（例如，未阻止）并且新优先级高于当前运行的任务，则可能发生上下文切换。
 * @param task 要检查的任务的句柄
 * @param prio   任务的优先级。
 */
    void task_set_priority(task_t task, uint32_t prio);
    /**
 * 返回指定任务的状态。
 * @param  task 要检查的任务的句柄
 * @return     任务的状态。（见task_state_e_t）。
 */
    task_state_e_t task_get_state(task_t task);

    /**
 * 暂停任务
 * @param task 任务的句柄
 */
    void task_suspend(task_t task);

    /**
 * 恢复被暂停的任务
 * @param task 任务的句柄
 */
    void task_resume(task_t task);

    /**
 * 返回内核当前正在管理的任务数，包括所有就绪，阻止或挂起的任务。
 * 已被删除但尚未被空闲任务获取的任务也将包含在计数中。最近创建的任务可能需要计算一个上下文切换。
 * @return  内核当前正在管理的任务数
 */
    uint32_t task_get_count(void);

    /**
 * 获取指定任务的名称。
 * @param  task 要检查的任务的句柄
 * @return     返回：指向任务名称的指针
 */
    char *task_get_name(task_t task);

    /**
 * 从指定的名称获取任务句柄。操作需要相当长的时间，应谨慎使用。
 * @param  name 要查询的名称
 * @return      具有匹配名称的任务句柄，如果未找到，则返回 NULL。
 */
    task_t task_get_by_name(const char *name);
    /**
 *向任务发送简单通知并递增通知计数器。
 * @param  task 通知任务的句柄
 * @return      始终为真。
 */
    uint32_t task_notify(task_t task);

    /**
 * 向任务发送通知，可选择执行某些操作。在修改通知值之前，还将检索目标任务中的通知值。
 * @param  task       通知任务的句柄
 * @param  value      执行操作时使用的值
 * @param  action     	可选地执行任务通知的操作
 * @param  prev_value 	存储目标任务的通知的先前值的指针可以是NULL
 * @return            取决于通知操作。对于NOTIFY_ACTION_NO_OWRITE：如果可以在不需要覆盖的情况下写入值，则返回0，否则返回1。对于所有其他NOTIFY_ACTION值：始终返回0
 */
    uint32_t task_notify_ext(task_t task, uint32_t value, notify_action_e_t action, uint32_t *prev_value);

    /**
 * 等待通知非零。
 * @param  clear_on_exit 如果为真（1），则清除通知值。如果为false（0），则通知值递减。
 * @param  timeout      指定等待通知发生的时间。
 * @return              递减或清除任务的通知值之前的值。
 */
    uint32_t task_notify_take(bool clear_on_exit, uint32_t timeout);

    /**
 * 清除任务通知。
 * @param  task 清除任务的句柄
 * @return      如果没有等待通知则返回 False，如果有，则返回 true
 */
    bool task_notify_clear(task_t task);

    /**
 * 创建一个互斥锁 例:mutex_t 互斥锁1号 = mutex_create();
 * @return  新创建的mutex_t的句柄。如果发生错误，将返回NULL并errno可以检查有关mutex_create失败原因的提示。
 */
    mutex_t mutex_create(void);

    /**
 * 取出并锁定一个mutex_t，在超时之前等待一定的毫秒数。
 * @param  mutex   要使用的互斥量。
 * @param  timeout 在互斥锁可用之前等待的时间。超时0可用于轮询mutex_t。TIMEOUT_MAX可用于无限期阻止。
 * @return         如果成功获取互斥锁，则返回 true，否则返回 false。如果返回false，则errno设置一个提示，说明无法获取互斥锁的原因
 */
    bool mutex_take(mutex_t mutex, uint32_t timeout);

    /**
 * 解锁一个互斥锁
 * @param  mutex 互斥锁的名字
 * @return       如果成功返回互斥锁，则返回true，否则返回false。如果返回false，则errno设置一个提示，说明无法返回互斥锁的原因。
 */
    bool mutex_give(mutex_t mutex);

#ifdef __cplusplus
    } // namespace c
    } // namespace pros
}
#endif

#endif // _PROS_RTOS_H_

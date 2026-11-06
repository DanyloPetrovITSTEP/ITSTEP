using System;
using System.Collections.Generic;
using System.Reflection;

namespace Lesson13.Practice
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NotificationAttribute(string name) : Attribute
    {
        public string Name { get; init; } = name;
        public int Priority { get; set; } = 0;
        public bool ExecuteOnce { get; set; } = false;

    }

    public class NotificationHandler
    {
        public Action Action { get; set; }
        public int Priority { get; set; }
        public bool ExecuteOnce { get; set; }

        public NotificationHandler(Action action, int priority, bool execute)
        {
            Action = action;
            Priority = priority;
            ExecuteOnce = execute;
        }
    }

    public class NotificationCenter
    {
        private readonly Dictionary<string, List<NotificationHandler>> _notifications = new();

        public void Register(object target)
        {
            var targetType = target.GetType();

            foreach (var method in targetType.GetMethods())
            {
                var attribute = method.GetCustomAttribute<NotificationAttribute>();

                if (attribute is null) continue;

                var action = Delegate.CreateDelegate(typeof(Action), target, method) as Action;

                if (action is not null)
                {
                    var handler = new NotificationHandler(action, attribute.Priority, attribute.ExecuteOnce);

                    if (_notifications.TryGetValue(attribute.Name, out var actions)) actions.Add(handler);
                    else _notifications.Add(attribute.Name, [handler]);
                }
            }
        }

        public void Notify(string name)
        {
            if (_notifications.TryGetValue(name, out var handlers))
            {
                var sortedHandlers = handlers.OrderByDescending(handler => handler.Priority).ToList();

                foreach (var handler in sortedHandlers)
                {
                    handler.Action();
                    if (handler.ExecuteOnce) handlers.Remove(handler);
                }

                if (handlers.Count == 0) _notifications.Remove(name);
            }
            else Console.WriteLine("Notification not found: " + name);
        }

        public void Unregister(object target)
        {
            var targetType = target.GetType();

            foreach (var method in targetType.GetMethods())
            {
                var attribute = method.GetCustomAttribute<NotificationAttribute>();

                if (attribute is null) continue;

                var action = Delegate.CreateDelegate(typeof(Action), target, method) as Action;

                if(action is not null && _notifications.TryGetValue(attribute.Name, out var handlers))
                {
                    handlers.RemoveAll(handler => handler.Action == action);
                    if (handlers.Count == 0) _notifications.Remove(attribute.Name);
                }
            }
        }
    }

    public class EmailService
    {
        [Notification("OrderCreated")]
        public void OrderCreated() => Console.WriteLine("Email: Order created");

        [Notification("OrderShipped")]
        public void OrderShipped() => Console.WriteLine("Email: Order shipped");
    }

    public class SmsService
    {
        [Notification("OrderShipped")]
        public void OrderShipped() => Console.WriteLine("SMS: Order shipped");
    }

    public class AnalyticsService
    {
        [Notification("OrderCreated")]
        public void OrderCreated() => Console.WriteLine("Analytics: Order created");

        [Notification("OrderShipped")]
        public void OrderShipped() => Console.WriteLine("Analytics: Order shipped");
    }
}

using System;
using System.Collections.Generic;
using System.Text;

using Lesson13.Practice;

NotificationCenter center = new NotificationCenter();

EmailService email = new EmailService();
SmsService sms = new SmsService();
AnalyticsService analytics = new AnalyticsService();

center.Register(email);
center.Register(sms);
center.Register(analytics);

Console.WriteLine("====== Order Created ======");
center.Notify("OrderCreated");

Console.WriteLine("\n====== Order Shipped ======");
center.Notify("OrderShipped");

center.Unregister(email);

Console.WriteLine("\n====== Unregister ======");
center.Notify("OrderCreated");


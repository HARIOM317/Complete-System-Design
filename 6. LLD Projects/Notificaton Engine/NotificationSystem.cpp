#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "TimeUtils.h"

using namespace std;

/*============================
    Notification & Decorators
=============================*/

// Interface
class INotification
{
public:
    virtual string getContent() const = 0;
    virtual ~INotification() {}
};

// Concrete Notification: Simple text notification.
class SimpleNotification : public INotification
{
private:
    string text;

public:
    SimpleNotification(const string &msg) : text(msg) {}

    string getContent() const override
    {
        return text;
    }
};

// Abstract Decorator: Wraps a Notification object.
class INotificationDecorator : public INotification
{
protected:
    INotification *notification;

public:
    INotificationDecorator(INotification *n)
    {
        notification = n;
    }

    virtual ~INotificationDecorator()
    {
        delete notification;
    }
};

// Decorator to add a timestamp to the content.
class TimestampDecorator : public INotificationDecorator
{
    string currTime = TimeUtils::getCurrentTime();

public:
    TimestampDecorator(INotification *n) : INotificationDecorator(n) {}

    string getContent() const override
    {
        return currTime + " " + notification->getContent();
    }
};

// Decorator to append a signature to the content.
class SignatureDecorator : public INotificationDecorator
{
private:
    string signature;

public:
    SignatureDecorator(INotification *n, const string &sign) : INotificationDecorator(n)
    {
        signature = sign;
    }

    string getContent() const override
    {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};

/*============================
  Observer Pattern Components
=============================*/

// Observer interface: each observer gets an update with a Notification pointer.
class IObserver
{
public:
    virtual void update() = 0;
    virtual ~IObserver() {}
};

// Interface
class IObservable
{
public:
    virtual void addObserver(IObserver *observer) = 0;
    virtual void removeObserver(IObserver *observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Observable
class NotificationObservable : public IObservable
{
private:
    vector<IObserver *> observers;
    INotification *currentNotification;

public:
    NotificationObservable()
    {
        currentNotification = nullptr;
    }

    void addObserver(IObserver *observer) override
    {
        observers.push_back(observer);
    }

    void removeObserver(IObserver *observer) override
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override
    {
        for (unsigned int i = 0; i < observers.size(); i++)
        {
            observers[i]->update();
        }
    }

    void setNotification(INotification *notification)
    {
        if (currentNotification != nullptr)
        {
            delete currentNotification;
        }
        currentNotification = notification;
        notifyObservers();
    }

    INotification *getNotification()
    {
        return currentNotification;
    }

    string getNotificationContent()
    {
        return currentNotification->getContent();
    }

    ~NotificationObservable()
    {
        if (currentNotification != nullptr)
        {
            delete currentNotification;
        }
    }
};

/*============================
    NotificationService
=============================*/

/* The NotificationService manages notifications. It keeps track of notifications. Any client code will interact with this service.*/

// Singleton class
class NotificationService
{
private:
    NotificationObservable *observable;
    static NotificationService *instance;
    vector<INotification *> notifications;

    // private constructor
    NotificationService()
    {
        observable = new NotificationObservable();
    }

public:
    static NotificationService *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new NotificationService();
        }
        return instance;
    }

    // Expose the observable so observers can attach.
    NotificationObservable *getObservable()
    {
        return observable;
    }

    // Creates a new Notification and notifies observers.
    void sendNotification(INotification *notification)
    {
        notifications.push_back(notification);
        observable->setNotification(notification);
    }

    ~NotificationService()
    {
        delete observable;
    }
};

NotificationService *NotificationService::instance = nullptr;

/*============================
    ConcreteObservers
=============================*/

class Logger : public IObserver
{
private:
    NotificationObservable *notificationObservable;

public:
    Logger()
    {
        this->notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }

    Logger(NotificationObservable *observable)
    {
        this->notificationObservable = observable;
        notificationObservable->addObserver(this);
    }

    void update()
    {
        cout << "Logging New Notification : \n"
             << notificationObservable->getNotificationContent() << endl;
        ;
    }
};

/*============================
  Strategy Pattern Components
  (Concrete Observer 2)
=============================*/

// Abstract class for different Notification Strategies.
class INotificationStrategy
{
public:
    virtual void sendNotification(string content) = 0;
};

// For email notifications
class EmailStrategy : public INotificationStrategy
{
private:
    string emailId;

public:
    EmailStrategy(string emailId)
    {
        this->emailId = emailId;
    }

    void sendNotification(string content) override
    {
        // Simulate the process of sending an email notification, representing the dispatch of messages to users via email.​

        cout << "Sending email Notification to: " << emailId << endl;
        cout << content << endl;
    }
};

// For sms notifications
class SMSStrategy : public INotificationStrategy
{
private:
    string mobileNumber;

public:
    SMSStrategy(string mobileNumber)
    {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override
    {
        // Simulate the process of sending an SMS notification, representing the dispatch of messages to users via SMS.​

        cout << "Sending SMS Notification to: " << mobileNumber << "\n"
             << content << endl;
    }
};

// For pop-up notifications
class PopUpStrategy : public INotificationStrategy
{
public:
    void sendNotification(string content) override
    {
        // Simulate the process of sending popup notification.
        cout << "Sending Popup Notification: \n"
             << content;
    }
};

// _____ Notification Engine _____
class NotificationEngine : public IObserver
{
private:
    NotificationObservable *notificationObservable;
    vector<INotificationStrategy *> notificationStrategies;

public:
    NotificationEngine()
    {
        this->notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }

    NotificationEngine(NotificationObservable *observable)
    {
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(INotificationStrategy *ns)
    {
        this->notificationStrategies.push_back(ns);
    }

    // Can have RemoveNotificationStrategy as well.

    void update()
    {
        string notificationContent = notificationObservable->getNotificationContent();

        for (const auto notificationStrategy : notificationStrategies)
        {
            notificationStrategy->sendNotification(notificationContent);
        }
    }
};

int main()
{
    // Create NotificationService
    NotificationService *notificationService = NotificationService::getInstance();

    // Create Logger Observer
    Logger *logger = new Logger();

    // Create NotificationEngine Observer
    NotificationEngine *notificationEngine = new NotificationEngine();

    notificationEngine->addNotificationStrategy(new EmailStrategy("xyz.person@gmail.com"));

    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 8765309873"));

    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    // Create a notification with decorators
    INotification *notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");

    notificationService->sendNotification(notification);

    // Cleanup
    delete logger;
    delete notificationEngine;

    return 0;
}
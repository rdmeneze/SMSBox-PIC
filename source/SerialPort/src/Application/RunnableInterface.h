#ifndef __RUNNABLEINTERFACE__
#define __RUNNABLEINTERFACE__

class IRunnable {
  public:
    virtual int Run( ) = 0;
    virtual ~IRunnable() {};
};

#endif // ~__RUNNABLEINTERFACE__

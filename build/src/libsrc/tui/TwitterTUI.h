#ifndef __TWEETRTUI_H__
#define __TWEETRTUI_H__

#include <iostream>

#ifdef __CYGWIN__
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

#include <list>
#include <vector>
#include <sstream>
#include "src/libsrc/wrapper/wrapper.h"
#include <time.h>
#include "./config.h"
#include "src/libsrc/pluginarch/PluginLoader.h"
#include "src/libsrc/search/PrefixSearch.h"
#include "src/libsrc/config/TweetxConfig.h"
#include "src/libsrc/spellcheck/spellcheck.h"

namespace Tweeter
{

  enum enWindowType{
    WT_BROWSER=0,
    WT_STATUS_BAR=1,
    WT_SYSTEM_BAR=2,
    WT_COMMAND_BAR=3
  };

  class TweetxTUI;
  class CursesWindow;
  typedef int Points;
  typedef int Colors;
  typedef int CoOrdinates;
  typedef int KeyBoardChar;
  typedef std::vector<CursesWindow*> CurseWindowPtrVector;

  template <typename T>
    class CallBackSimulator
    {
      T* mRef;
      public:
      CallBackSimulator(T* pRef):mRef(pRef){}
      ~CallBackSimulator(){mRef=NULL;}
      void operator()(std::vector<KeyBoardChar> &pKeyBuffer)
      {
        mRef->mHandleKeyBoard(pKeyBuffer);
      }
    };

  /* Should make it singleton later */
  class NCursesEnv
  {
    public:
      NCursesEnv();
      ~NCursesEnv();
      static void init();
      static void end();
  };

  class CursesWindow
  {
    protected:
      CoOrdinates mXCord;
      CoOrdinates mYCord;
      Colors mBackground;
      Colors mTextColor;

      Points mHeight;
      Points mWidth;

      Points mMaxHeight;
      Points mMaxWidth;

      WINDOW *mWinPtr;

      std::string mContent;

    public:
      CursesWindow();
      virtual ~CursesWindow();
      WINDOW* getWindow(){return mWinPtr;}
      std::string &getContent(){return mContent;}
      void mCreateWin(CoOrdinates pYCord, CoOrdinates pXCord, Points pHeight, Points pWidth);

      virtual void mResize() = 0;
      virtual void mRefresh() = 0;
      virtual void mColoring() = 0;
      virtual void mHandleKeyBoard(std::vector<KeyBoardChar> &) = 0; 
  };

  class StatusBar:public CursesWindow
  {
    public:
      StatusBar();
      void mResize();
      void mRefresh();
      void mColoring();
      void mHandleKeyBoard(std::vector<KeyBoardChar> &a){} 
  };

  class Browser:public CursesWindow
  {
    public:
      Browser();
      void mResize();
      void mRefresh();
      void mColoring();
      void mHandleKeyBoard(std::vector<KeyBoardChar> &a){} 
  };

  class SystemBar:public CursesWindow
  {
    public:
      SystemBar();
      void mResize();
      void mRefresh();
      void mColoring();
      void mHandleKeyBoard(std::vector<KeyBoardChar> &a){} 
  };

  class CommandBar:public CursesWindow
  {
      std::string mDisplayContent;
    public:
      CommandBar();
      void mResize();
      void mRefresh();
      void mColoring();
      void mHandleKeyBoard(std::vector<KeyBoardChar> &);
      void mReAlignCommand(std::string&);
  };

  class KeyBoardHandler
  {
    std::vector<KeyBoardChar> mKeyBuffer;
    public:
    KeyBoardHandler(){mKeyBuffer.clear();}
    ~KeyBoardHandler(){mKeyBuffer.clear();}
    void readKeyBoard(CursesWindow &pWin,CallBackSimulator<TweetxTUI>& pCallBack)
    {
      KeyBoardChar tGetKey;
      while(tGetKey = wgetch(pWin.getWindow()))
      {
          mKeyBuffer.push_back(tGetKey);
          pCallBack(mKeyBuffer);
      }
    }

    std::vector<KeyBoardChar> &getKeyBuffer(){return mKeyBuffer;}
  };

  class CommandExec
  {
    int mCurrentCommandNode;
    TweetxTUI* mTweetxTUI;
    std::string mRunningCommand;
    std::vector<std::string> mHistory;
    std::vector<std::string> mCommand;
    CurseWindowPtrVector mSubWindows;

    //replace with PluginFactory
    std::map<std::string,PluginProperties*> mCommander;
    std::map<std::string,std::string> mCommandHelp;
    /* Save's data from recent */
    std::map<std::string,Wrapper::WrapperItem> mRecentTweets;

    bool showError(TweetxError);

    public:
    CommandExec(CurseWindowPtrVector &,TweetxTUI*);
    ~CommandExec();
    TweetxTUI* getTuiInstance(){return mTweetxTUI;}
    void setTuiInstance(TweetxTUI* pTweetxTUI){mTweetxTUI=pTweetxTUI;}
    void manageCommands(std::vector<KeyBoardChar> &);
    void mHandleEnterKey(std::vector<KeyBoardChar> &);
    void mHandleArrowKey(int);

    void deleteTweet(std::vector<std::string>&);
    void getFriendTimeline(std::vector<std::string>&);
    void doRetweet(std::vector<std::string> &pArgs);
    void setNewStatus(std::vector<std::string> &pStatus);
    std::string getHistoryData(int);
    void hHandleTABKey();

    void mGenericExec(std::string ,std::vector<std::string>&);
  };


  class TweetxTUI
  {
    CommandExec *mCommandExec;
    ProxyLoader mPluginHandler;
    std::vector<CursesWindow*> mSubWindows;
    public:
    TweetxTUI();
    ~TweetxTUI();
    void mHandleKeyBoard(std::vector<KeyBoardChar> &pKeyBuff);
    ProxyLoader& getPluginLoader(){return mPluginHandler;}
  };

}

#endif

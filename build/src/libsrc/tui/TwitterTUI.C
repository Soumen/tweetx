#include "TwitterTUI.h"

namespace Tweeter
{
  void NCursesEnv::init()
  {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);

    //define color set here.
  }

  void NCursesEnv::end()
  {
    endwin();
  }

  /* Empty Constructor */
  CursesWindow::CursesWindow()
  {
    mXCord = 0;
    mYCord = 0;
    mHeight = 0;
    mWidth = 0;
    mWinPtr = NULL;
  }

  /* Creates the memory for the WINDOW pointer */
  void CursesWindow::mCreateWin
    (CoOrdinates pYCord, CoOrdinates pXCord, Points pHeight, Points pWidth)
    {
      mYCord = pYCord;
      mXCord = pXCord;

      mHeight = pHeight;
      mWidth = pWidth;

      //add error handling
      mWinPtr = newwin(pHeight,pWidth,pYCord,pXCord);
    }

  /* Deletes mWinPtr dont do it again in derived */
  CursesWindow::~CursesWindow()
  {
    if(mWinPtr!=NULL)
      delwin(mWinPtr);
  }

  // STATUS-BAR
  StatusBar::StatusBar()
  {
    getmaxyx(stdscr,mMaxHeight,mMaxWidth);
    mCreateWin(0,0,1,mMaxWidth);
    if(has_colors()!=false)
    {
      start_color();
      init_pair(1,COLOR_WHITE,COLOR_CYAN);
      wbkgd(mWinPtr,A_BOLD | COLOR_PAIR(1));
      mContent = PACKAGE_STRING;
      int iSpaceSize = (mMaxWidth - mContent.length() )/2;
      mContent = "";
      for(int iCount=0;iCount<iSpaceSize;iCount++)
        mContent += " ";
      mContent += PACKAGE_STRING;
      waddstr(mWinPtr,mContent.c_str());
    }
    mRefresh();
  }

  void StatusBar::mResize()
  {
  }

  void StatusBar::mRefresh()
  {
    wrefresh(mWinPtr);
  }

  void StatusBar::mColoring()
  {
  }

  //BROWSER
  Browser::Browser()
  {
    getmaxyx(stdscr,mMaxHeight,mMaxWidth);
    mCreateWin(1,0,mMaxHeight-3,mMaxWidth);
    if(has_colors()!=false)
    {
      use_default_colors();
      scrollok(mWinPtr,TRUE);
    }
    mRefresh();
  }

  void Browser::mResize()
  {
  }

  void Browser::mRefresh()
  {
    wrefresh(mWinPtr);
  }

  void Browser::mColoring()
  {
  }

  //SystemBar
  SystemBar::SystemBar()
  {
    getmaxyx(stdscr,mMaxHeight,mMaxWidth);
    mCreateWin(mMaxHeight-2,0,1,mMaxWidth);
    if(has_colors()!=false)
    {
      start_color();
      init_pair(1,COLOR_WHITE,COLOR_CYAN);
      wbkgd(mWinPtr,A_BOLD | COLOR_PAIR(1));
    }
    mRefresh();
  }

  void SystemBar::mResize()
  {
  }

  void SystemBar::mRefresh()
  {
    wrefresh(mWinPtr);
  }

  void SystemBar::mColoring()
  {
  }


  //CommandBar
  CommandBar::CommandBar()
  {
    getmaxyx(stdscr,mMaxHeight,mMaxWidth);
    mCreateWin(mMaxHeight-1,0,1,mMaxWidth);
    if(has_colors()!=false)
    {
      use_default_colors();
    }
    mRefresh();
  }

  void CommandBar::mHandleKeyBoard(std::vector<KeyBoardChar> &pKeyBuff)
  {
    /* 
     * 10   - Enter
     * 127  - Backspace
     */
    if(pKeyBuff.size()>0)
    {
      KeyBoardChar tBuff = *(pKeyBuff.begin());
      switch(tBuff)
      {
        case 10:
          werase(mWinPtr);
          mContent.clear();
          break;
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_UP:
        case KEY_DOWN:
          break;
        case KEY_BACKSPACE:
          if(mContent.length()>0)
          {
            mContent = mContent.substr(0,mContent.length()-1);
	    mDisplayContent=mContent;
	    mReAlignCommand(mDisplayContent);
            werase(mWinPtr);
            waddstr(mWinPtr,mDisplayContent.c_str());
          }
          break;
        default:
	  {
          std::stringstream tStr;
          tStr<<(char)tBuff;
          mContent += tStr.str();
          werase(mWinPtr);
	  mDisplayContent=mContent;
	  mReAlignCommand(mDisplayContent);
          waddstr(mWinPtr,mDisplayContent.c_str());
          break;
	  }
      }
      pKeyBuff.clear();
      mRefresh();
    }
  }

  void CommandBar::mReAlignCommand(std::string& pInput)
  {
	  if(pInput.length()>mWidth)
		  pInput=pInput.substr
			  (pInput.length()-mWidth,mWidth);
  }

  void CommandBar::mResize()
  {
  }

  void CommandBar::mRefresh()
  {
    wrefresh(mWinPtr);
  }

  void CommandBar::mColoring()
  {
  }

  //CommandExec 
  CommandExec::CommandExec(CurseWindowPtrVector &pWindowList,TweetxTUI* pTUI)
  {
    mTweetxTUI = pTUI;
    for(CurseWindowPtrVector::iterator itrWinList = pWindowList.begin();
        pWindowList.size()>0 && itrWinList != pWindowList.end();
        itrWinList++)
    {
      mSubWindows.push_back(*itrWinList);
    }
    mCommander["/recent"]=NULL;
    mCommander["/help"]=NULL;
    mCommander["/tweet"]=NULL;
    mCommander["/me"]=NULL;
    mCommander["/retweet"]=NULL;
    mCommander["/delete"]=NULL;
    mCommander["/exit"]=NULL;
    mCommander["/quit"]=NULL;

    //load all plugins here
    std::vector<std::string> tVecAutoPopulation;
    for(std::map<std::string,PluginProperties*>::iterator itr=mCommander.begin();mCommander.size()>0 && itr!=mCommander.end(); itr++)
    { tVecAutoPopulation.push_back(itr->first); }

    ProxyLoader &tPluginLoader = mTweetxTUI->getPluginLoader();
    std::map<std::string,PluginProperties *> &tPluginProxy = tPluginLoader.mPluginProxy;

    for(std::map<std::string,PluginProperties *>::iterator itrPlugins = tPluginProxy.begin();tPluginProxy.size()>0 && itrPlugins!=tPluginProxy.end(); itrPlugins++)
    { tVecAutoPopulation.push_back(itrPlugins->first); }
    PREFIX_POPULATE(tVecAutoPopulation);
  }

  CommandExec::~CommandExec()
  {
    mSubWindows.clear();
  }

  void CommandExec::mGenericExec(std::string pCommand,std::vector<std::string> &pArgs)
  {
    if(pCommand.find("/exit")!=std::string::npos
        && pCommand.find("/exit") == 0)
    { throw 911; return; }

    if(pCommand.find("/quit")!=std::string::npos
        && pCommand.find("/quit") == 0)
    { throw 911; return; }

    if(pCommand.find("/recent")!=std::string::npos
        && pCommand.find("/recent") == 0)
    { getFriendTimeline(pArgs); return; }

    if(pCommand.find("/retweet")!=std::string::npos
        && pCommand.find("/retweet") == 0)
    { doRetweet(pArgs); return; }

    if(pCommand.find("/delete")!=std::string::npos
        && pCommand.find("/delete") == 0)
    { deleteTweet(pArgs); return; }

    if(pCommand.find("/tweet")!=std::string::npos
        && pCommand.find("/tweet") == 0)
    { setNewStatus(pArgs); return; }

    if(pCommand.find("/me")!=std::string::npos
        && pCommand.find("/me") == 0)
    { 
      std::string stdGetMeValue = "***";
      stdGetMeValue += GetConfig(CP_USERNAME);
      pArgs.insert(pArgs.begin(),stdGetMeValue);
      setNewStatus(pArgs);
      return; 
    }

    ProxyLoader &tPluginLoader = mTweetxTUI->getPluginLoader();
    std::map<std::string,PluginProperties *> &tPluginProp = tPluginLoader.mPluginProxy;

    if(tPluginProp.find(pCommand)!=tPluginProp.end())
    {
      PluginProperties &tProperties = *(tPluginProp[pCommand]);
      if(tProperties.mIsBackGroundProcess)
      {
        mSubWindows[WT_BROWSER]->mRefresh();
        //also check isEnabled.
        //Run in background
        if(pArgs.size()>0)
        {
          std::string tStatus = *(pArgs.begin());
          pArgs.erase(pArgs.begin());
          if(tStatus=="START")
          {
            waddstr(mSubWindows[WT_BROWSER]->getWindow(),"\n[EXECUTED:");
            waddstr(mSubWindows[WT_BROWSER]->getWindow(),pCommand.c_str());
            waddstr(mSubWindows[WT_BROWSER]->getWindow(),"{daemon}]\n");
            if(tProperties.mDerivePluginObject!=NULL)
            { tProperties.mDerivePluginObject->mPluginStatus = true; }
            tPluginLoader.executeCommand(pCommand,pArgs);
            mSubWindows[WT_BROWSER]->mRefresh();
          }
          if(tStatus=="STOP")
          {
            waddstr(mSubWindows[WT_BROWSER]->getWindow(),"\n[TERMINATED:");
            waddstr(mSubWindows[WT_BROWSER]->getWindow(),pCommand.c_str());
            waddstr(mSubWindows[WT_BROWSER]->getWindow(),"{daemon}]\n");
            if(tProperties.mDerivePluginObject!=NULL)
            { tProperties.mDerivePluginObject->mPluginStatus = false; }
            mSubWindows[WT_BROWSER]->mRefresh();
          }
        }
      }
      else
      {
        std::string tRetVal;
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),"\n[EXECUTED:");
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),pCommand.c_str());
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),"]\n");
        tRetVal = tPluginLoader.executeCommand(pCommand,pArgs);
        if(!tRetVal.empty())
        {
          waddstr(mSubWindows[WT_BROWSER]->getWindow(),tRetVal.c_str());
          mSubWindows[WT_BROWSER]->mRefresh();
        }
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),"\n[TERMINATED:");
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),pCommand.c_str());
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),"]\n");
        mSubWindows[WT_BROWSER]->mRefresh();
      }
      return;
    }

    waddstr(mSubWindows[WT_BROWSER]->getWindow(),"try help\n");
    mSubWindows[WT_BROWSER]->mRefresh();
  }

  void CommandExec::mHandleArrowKey(int pMover)
  {
    if((mCurrentCommandNode>=mHistory.size())
        && (mRunningCommand==""))
      mRunningCommand = mSubWindows[WT_COMMAND_BAR]->getContent();

    std::string tCurrComm = getHistoryData(pMover);
    werase(mSubWindows[WT_COMMAND_BAR]->getWindow());

    if(tCurrComm=="")
      tCurrComm = mRunningCommand;
    mSubWindows[WT_COMMAND_BAR]->getContent() = tCurrComm;
    waddstr(mSubWindows[WT_COMMAND_BAR]->getWindow(),tCurrComm.c_str());
    mSubWindows[WT_COMMAND_BAR]->mRefresh();
  }

  void CommandExec::mHandleEnterKey(std::vector<KeyBoardChar> &pKeyBuff)
  {
    std::string &strCommand = mSubWindows[WT_COMMAND_BAR]->getContent();
    if(strCommand.size()>0 )
    {
      mHistory.push_back(strCommand);
      mCurrentCommandNode = mHistory.size();
      mRunningCommand="";
      std::vector<std::string> tTokenized;
      NSCommon::Tokenize(strCommand,tTokenized," ");
      char tFirstChar = *(tTokenized.front().begin());
      std::string strFirstCommand = *(tTokenized.begin());

      if(tFirstChar != '/')
      { strFirstCommand = "/tweet"; }
      else
      {tTokenized.erase(tTokenized.begin());}

      CommandExec::mGenericExec(strFirstCommand,tTokenized);
    }
    mSubWindows[WT_COMMAND_BAR]->getContent() = "";
    mSubWindows[WT_COMMAND_BAR]->mHandleKeyBoard(pKeyBuff);
  }

  void CommandExec::hHandleTABKey()
  {
    std::string &strCommand = mSubWindows[WT_COMMAND_BAR]->getContent();
    if(strCommand.size()>0 )
    {
      std::vector<std::string> tTokenized;
      NSCommon::Tokenize(strCommand,tTokenized," ");
      char tFirstChar = *(tTokenized.front().begin());
      char tATChar = *(tTokenized.back().begin());

      std::string strFirstCommand = *(tTokenized.begin());
      std::string strLastLetter = tTokenized.back();

      std::vector<std::string> tPossibleComm;

      if(tTokenized.size()==1 && tFirstChar == '/')
      { 
        tTokenized.erase(tTokenized.begin());
        PREFIX_GET_ENTRY(strFirstCommand,tPossibleComm); 
      }

      if(tTokenized.size()>0 && tATChar == '@')
      { 
        tTokenized.pop_back();
        PREFIX_FRIEND_GET_ENTRY(strLastLetter,tPossibleComm); 
      }

      if(tPossibleComm.size()==1)
      {
        std::string strNewComm;
        for(std::vector<std::string>::iterator itr = tTokenized.begin();
            tTokenized.size()>0 && itr!=tTokenized.end(); itr++)
        {
          strNewComm += *itr;
          strNewComm += " ";
        }
        if(strNewComm == " ")
          strNewComm = "";

        strNewComm += tPossibleComm.front();

        werase(mSubWindows[WT_COMMAND_BAR]->getWindow());
        waddstr(mSubWindows[WT_COMMAND_BAR]->getWindow(),strNewComm.c_str());
        mCurrentCommandNode = mHistory.size();
        mSubWindows[WT_COMMAND_BAR]->getContent() = strNewComm;
        mRunningCommand=mSubWindows[WT_COMMAND_BAR]->getContent();
      }

      for(std::vector<std::string>::iterator itr = tPossibleComm.begin();
          tPossibleComm.size()>0 && tPossibleComm.size()!=1 
          && itr!=tPossibleComm.end(); itr++)
      {
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),(itr->substr(1,itr->length()-1)).c_str());
        waddstr(mSubWindows[WT_BROWSER]->getWindow(),"\n");
      }
    }
    mSubWindows[WT_BROWSER]->mRefresh();
  }

  void CommandExec::manageCommands(std::vector<KeyBoardChar> &pKeyBuff)
  {
    //Handling Inputs.
    switch(*(pKeyBuff.begin()))
    {
      case 10:
        //ENTER
        mHandleEnterKey(pKeyBuff);
        break;
      case KEY_DOWN:
        mHandleArrowKey(+1);
        break;
      case KEY_UP:
        mHandleArrowKey(-1);
        break;
      case 9:
        //TAB
        hHandleTABKey();
        break;
      default:
        {
          //Handling Function keys.
          if(*(pKeyBuff.begin()) == KEY_F(2))
          {
            std::string tNewCommand;
            std::vector<std::string> tTokenized;
            std::vector<std::string> tDictionary;
            std::string tContent = mSubWindows[WT_COMMAND_BAR]->getContent();
            NSCommon::Tokenize(tContent,tTokenized," ");
            if(tTokenized.size()>0)
            {
              SpellChecker sc("words","words.soundex","words.cache");
              sc.RunSetup();
              sc.GetSpellSuggestions(*(tTokenized.rbegin()),tDictionary);
            }

            int i4Count=1;
            for(std::vector<std::string>::iterator itr = tDictionary.begin();
                tDictionary.size()>0 && itr!=tDictionary.end(); itr++)
            {
              waddstr(mSubWindows[WT_BROWSER]->getWindow(),(*itr).c_str());
              waddstr(mSubWindows[WT_BROWSER]->getWindow(),"   ");
              if(i4Count%4==0)
              waddstr(mSubWindows[WT_BROWSER]->getWindow(),"\n");
              mSubWindows[WT_BROWSER]->mRefresh();
              i4Count++;
            }
            break;
          }
          //Keep appending
          mSubWindows[WT_COMMAND_BAR]->mHandleKeyBoard(pKeyBuff);
          mCurrentCommandNode = mHistory.size();
          mRunningCommand=mSubWindows[WT_COMMAND_BAR]->getContent();
          break;
        }
    }
    mSubWindows[WT_COMMAND_BAR]->mRefresh();
    pKeyBuff.clear();
  }

  std::string CommandExec::getHistoryData(int pMoves)
  {
    mCurrentCommandNode+=pMoves;
    if(mCurrentCommandNode<=0)
    { mCurrentCommandNode=0; }

    if(mCurrentCommandNode>=mHistory.size())
    {
      mCurrentCommandNode = mHistory.size();
      return "";
    }
    return mHistory[mCurrentCommandNode];
  }

  void CommandExec::deleteTweet(std::vector<std::string> &pArgs)
  {
    std::string strAppend,strIndex;

    if(pArgs.size()>0)
    {
      strIndex = *(pArgs.begin());
      pArgs.erase(pArgs.begin());
      if(mRecentTweets.find(strIndex) != mRecentTweets.end())
      {
        strAppend += mRecentTweets[strIndex].id;
      }
    }
    Wrapper wrapper;
    std::vector<Wrapper::WrapperItem> myvect;
    wrapper.Send(Wrapper::DESTROY_STATUS, strAppend);
    if(!showError(wrapper.getError()))
      return;

    CursesWindow *tBrowser = mSubWindows[WT_BROWSER];
    CursesWindow *tStatusBar = mSubWindows[WT_STATUS_BAR];
    CursesWindow *tSystemBar = mSubWindows[WT_SYSTEM_BAR];
    CursesWindow *tCommandBar = mSubWindows[WT_COMMAND_BAR];

    waddstr(tBrowser->getWindow(), "<Deleted> [ ");
    if(has_colors()!=false)
    {
      start_color();
      init_pair(7,COLOR_RED,COLOR_WHITE);

      attr_t tAttrib;
      short tPair;
      wattr_get(tBrowser->getWindow(),&tAttrib,&tPair,NULL);
      wattron(tBrowser->getWindow(),A_BOLD | tPair);
    }
    waddstr(tBrowser->getWindow(), strIndex.c_str());
    wattroff(tBrowser->getWindow(),A_BOLD | COLOR_PAIR(7));

    waddstr(tBrowser->getWindow(), " ]");
    use_default_colors();

    time_t tCurrentTime;
    time( &tCurrentTime );
    werase(tSystemBar->getWindow());
    waddstr(tSystemBar->getWindow()," Status-Updated [ ");
    waddstr(tSystemBar->getWindow(),ctime(&tCurrentTime));
    waddstr(tSystemBar->getWindow()," ]");
    tSystemBar->mRefresh();

    waddstr(tBrowser->getWindow(),"\n");
    tBrowser->mRefresh();

  }

  void CommandExec::doRetweet(std::vector<std::string> &pArgs)
  {
    if(pArgs.size()>0)
    {
      std::string strIndex = *(pArgs.begin());
      std::string strAppend = "RT @";
      pArgs.erase(pArgs.begin());
      if(mRecentTweets.find(strIndex) != mRecentTweets.end())
      {
        strAppend += mRecentTweets[strIndex].user_screen_name;
        strAppend += " - ";
        strAppend += mRecentTweets[strIndex].text;
        pArgs.insert(pArgs.begin(),strAppend);
      }
      setNewStatus(pArgs);
    }
    pArgs.clear();
  }

  bool CommandExec::showError(TweetxError _te)
  {
    CursesWindow *tBrowser = mSubWindows[WT_BROWSER];
    LOG(LS_INFO) << "Wrapper Error Message: " << GetErrorDesc(_te);
    if(_te != TE_HTTP_OK)
    {
      waddstr(tBrowser->getWindow(),GetErrorDesc(_te));
      waddstr(tBrowser->getWindow(),"\n");
      tBrowser->mRefresh();
      return false;
    }
    else
      return true;

  }

  void CommandExec::setNewStatus(std::vector<std::string> &pArgs)
  {
    std::string pStatus;
    for(std::vector<std::string>::iterator itr = pArgs.begin();
        pArgs.size()>0 && itr!=pArgs.end(); itr++)
    {
      pStatus += *itr;
      pStatus += " ";
    }

    pStatus = pStatus.substr(0,pStatus.length()-1);

    Wrapper wrapper;
    std::vector<Wrapper::WrapperItem> myvect;
    wrapper.Send(Wrapper::NEW_STATUS, pStatus);
    if(!showError(wrapper.getError()))
      return;

    CursesWindow *tBrowser = mSubWindows[WT_BROWSER];
    CursesWindow *tStatusBar = mSubWindows[WT_STATUS_BAR];
    CursesWindow *tSystemBar = mSubWindows[WT_SYSTEM_BAR];
    CursesWindow *tCommandBar = mSubWindows[WT_COMMAND_BAR];

    waddstr(tBrowser->getWindow(), "<New-Status> [ ");
    if(has_colors()!=false)
    {
      start_color();
      init_pair(7,COLOR_RED,COLOR_WHITE);

      attr_t tAttrib;
      short tPair;
      wattr_get(tBrowser->getWindow(),&tAttrib,&tPair,NULL);
      wattron(tBrowser->getWindow(),A_BOLD | tPair);
    }
    waddstr(tBrowser->getWindow(), pStatus.c_str());
    wattroff(tBrowser->getWindow(),A_BOLD | COLOR_PAIR(7));

    waddstr(tBrowser->getWindow(), " ]");
    use_default_colors();

    time_t tCurrentTime;
    time( &tCurrentTime );
    werase(tSystemBar->getWindow());
    waddstr(tSystemBar->getWindow()," Status-Updated [ ");
    waddstr(tSystemBar->getWindow(),ctime(&tCurrentTime));
    waddstr(tSystemBar->getWindow()," ]");
    tSystemBar->mRefresh();

    waddstr(tBrowser->getWindow(),"\n");
    tBrowser->mRefresh();
  }


  void CommandExec::getFriendTimeline(std::vector<std::string> &pArgs)
  {
    Wrapper wrapper;
    std::string tPageValue = "NULL";
    std::vector<Wrapper::WrapperItem> myvect;
    if(pArgs.size()>0)
    {
      tPageValue = pArgs.front();
    }
    myvect = wrapper.Get(Wrapper::FRIENDS_TIMELINE, tPageValue);
    if(!showError(wrapper.getError()))
      return;

    CursesWindow *tBrowser = mSubWindows[WT_BROWSER];
    CursesWindow *tStatusBar = mSubWindows[WT_STATUS_BAR];
    CursesWindow *tSystemBar = mSubWindows[WT_SYSTEM_BAR];
    CursesWindow *tCommandBar = mSubWindows[WT_COMMAND_BAR];

    std::vector<std::string> tFriendList;
    std::stringstream strCount;
    int iCount = 1;
    mRecentTweets.clear();

    for(std::vector<Wrapper::WrapperItem>::reverse_iterator itr=myvect.rbegin();
        myvect.size()>0 && itr!=myvect.rend(); itr++,iCount++)
    {
      waddstr(tBrowser->getWindow(),"<");

      if(has_colors()!=false)
      {
        start_color();
        init_pair(7,COLOR_RED,COLOR_WHITE);

        attr_t tAttrib;
        short tPair;
        wattr_get(tBrowser->getWindow(),&tAttrib,&tPair,NULL);
        wattron(tBrowser->getWindow(),A_BOLD | tPair);
      }

      std::string tUserId = "@";
      tUserId += itr->user_screen_name;
      tFriendList.push_back(tUserId);

      waddstr(tBrowser->getWindow(), itr->user_screen_name.c_str());
      wattroff(tBrowser->getWindow(),A_BOLD | COLOR_PAIR(7));

      use_default_colors();

      strCount<<iCount;
      mRecentTweets[strCount.str()] = *itr;
      strCount.str("");
      strCount<<"["<<iCount<<"]> ";

      waddstr(tBrowser->getWindow(),strCount.str().c_str());
      waddstr(tBrowser->getWindow(), itr->text.c_str());
      waddstr(tBrowser->getWindow(),"\n");
      strCount.str("");
    }

    PREFIX_FRIEND_POPULATE(tFriendList);
    //PrefixSearch::mFriendPrefSearch->print();

    time_t tCurrentTime;
    time( &tCurrentTime );
    werase(tSystemBar->getWindow());
    waddstr(tSystemBar->getWindow()," Refreshed [ ");
    waddstr(tSystemBar->getWindow(),ctime(&tCurrentTime));
    waddstr(tSystemBar->getWindow()," ]");
    tSystemBar->mRefresh();

    waddstr(tBrowser->getWindow(),"\n");
    tBrowser->mRefresh();
  }



  //TWEETX-TUI

  TweetxTUI::TweetxTUI()
  {
    NCursesEnv::init();
    CursesWindow *tStatusBar = new StatusBar();
    CursesWindow *tBrowser = new Browser();
    CursesWindow *tSystemBar = new SystemBar();
    CursesWindow *tCommandBar = new CommandBar();
    keypad(tCommandBar->getWindow(),TRUE);

    /* Maintain the sequence (shall use map later) */
    mSubWindows.push_back(tBrowser);
    mSubWindows.push_back(tStatusBar);
    mSubWindows.push_back(tSystemBar);
    mSubWindows.push_back(tCommandBar);

    mPluginHandler.loadPlugin();
    mCommandExec = new CommandExec(mSubWindows,this);
    mCommandExec->setTuiInstance(this);

    CallBackSimulator<TweetxTUI> tCallback(this);

    KeyBoardHandler tKeyboard;
    try
    {
      tKeyboard.readKeyBoard(*(*(mSubWindows.rbegin())),tCallback);
    }
    catch(...)
    {std::cerr<<"i am out finally";}

    mPluginHandler.destroyPluginObj();
    NCursesEnv::end();
  }

  TweetxTUI::~TweetxTUI()
  {
    for(std::vector<CursesWindow*>::iterator itr = mSubWindows.begin();
        mSubWindows.size()>0 && itr!=mSubWindows.end(); itr++)
    {
      delete(*itr);
    }
    mSubWindows.clear();
    delete(mCommandExec);
  }

  void TweetxTUI::mHandleKeyBoard(std::vector<KeyBoardChar> &pKeyBuff)
  {
    mCommandExec->manageCommands(pKeyBuff);
  }
}

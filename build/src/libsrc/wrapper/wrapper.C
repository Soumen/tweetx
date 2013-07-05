#include "wrapper.h"


std::string Wrapper::HTTP_Dispatch(int dispatch_type, std::string url, bool auth, const std::string message)
{
    using namespace NSsocket;
    SocketAddress sa;
    sa.mHost = "www.twitter.com";
    sa.mPort = 443;
    sa.mConnType = CT_TLSV1;
    Http::HttpClient httpclient(sa);
    //httpclient = new Http::HttpClient(sa);
    Http::HttpMethod httpMethod;
    if(dispatch_type == GET)
      httpMethod = Http::GET;
    else if(dispatch_type == POST)
      httpMethod = Http::POST;
    else
    {
      LOG(LS_ERROR) << "The dispatch type is unknown";
      mError = TE_INVALID_OPTION;
      return "";
    }
    httpclient.setUsername(GetConfig(CP_USERNAME));
    httpclient.setPassword(GetConfig(CP_PASSWORD));
    if(dispatch_type == GET)
      httpclient.IntializeRequest(httpMethod,url,"www.twitter.com",auth);
    else if(dispatch_type == POST)
      httpclient.IntializeRequest(httpMethod,url,"www.twitter.com",auth, message);
    else
    {
      mError = TE_INVALID_OPTION;
      LOG(LS_ERROR) << "Invalid Option: GET or POST must be supplied";
      return "";
    }
    if(httpclient.Start() == SR_ERROR)
    {
      mError = TE_HTTP_SERVER_ERROR;
      LOG(LS_ERROR) << "Problem Connecting to Server! Aborting connection";
      return "";
    }

    Http::HttpResponseData &responseData = httpclient.getHttpResponse();
    mError = responseData.mStatus;
    return responseData.mData;
}


/* Parse XML and Place into Vector for each Item */
void Wrapper::Parse(const std::string &xml)
{
		if (mError != TE_WE_OK)
		{
			LOG(LS_ERROR) << "Could not parse from previous error in HTTP_DISPATCH, Aborting";
			return;
		}
    LOG(LS_INFO) << "Parsing XML";
    ticpp::Document doc;

    if(xml.empty() && mError != TE_WE_OK)
      return;
    try
    {
      doc.Parse(xml);
      ticpp::Element *ele_object = doc.FirstChildElement("statuses");
      ticpp::Iterator<ticpp::Element> entry(ele_object->FirstChildElement("status"), "status");

      while (entry != entry.end())
      {
        /* Construct one object for each <status> called item of nested class WrapperItem */
        WrapperItem item;

        /* Places XML into Elements */
        ticpp::Element *createdAtElement = entry->FirstChildElement("created_at", false);
        ticpp::Element *idElement = entry->FirstChildElement("id", false);
        ticpp::Element *textElement = entry->FirstChildElement("text", false);
        ticpp::Element *sourceElement = entry->FirstChildElement("source", false);
        ticpp::Element *truncatedElement = entry->FirstChildElement("truncated", false);
        ticpp::Element *in_reply_to_status_idElement = entry->FirstChildElement("in_reply_to_status_id", false);
        ticpp::Element *in_reply_to_user_idElement = entry->FirstChildElement("in_reply_to_user_id", false);
        ticpp::Element *favoritedElement = entry->FirstChildElement("favorited", false);
        // jump to next child <user>
        ticpp::Element *userElement = entry->FirstChildElement("user", false);
        // get all elements of <child>
        ticpp::Element *user_idElement = userElement->FirstChildElement("id", false);
        ticpp::Element *user_nameElement = userElement->FirstChildElement("name", false);
        ticpp::Element *user_screen_nameElement = userElement->FirstChildElement("screen_name", false);
        ticpp::Element *user_descriptionElement = userElement->FirstChildElement("description", false);
        ticpp::Element *user_locationElement = userElement->FirstChildElement("location", false);
        ticpp::Element *user_profile_image_urlElement = userElement->FirstChildElement("profile_image_url", false);
        ticpp::Element *user_protectedElement = userElement->FirstChildElement("protected", false);
        ticpp::Element *user_followers_countElement = userElement->FirstChildElement("followers_count", false);

        /* Get Text from each Element and store in variable */
        item.created_at              = createdAtElement->GetText();
        item.id                      = idElement->GetText();
        item.text                    = textElement->GetText();
        item.source                  = sourceElement->GetText();
        item.truncated               = truncatedElement->GetText();
        item.favorited               = favoritedElement->GetText();
        item.in_reply_to_status_id   = in_reply_to_status_idElement->GetTextOrDefault("0");
        item.in_reply_to_user_id     = in_reply_to_user_idElement->GetTextOrDefault("0");

        item.user_id                 = user_idElement->GetTextOrDefault("0");
        item.user_name               = user_nameElement->GetTextOrDefault("0");
        item.user_screen_name        = user_screen_nameElement->GetTextOrDefault("0");
        item.user_description        = user_descriptionElement->GetTextOrDefault("0");
        item.user_location           = user_locationElement->GetTextOrDefault("0");
        item.user_profile_image_url  = user_profile_image_urlElement->GetTextOrDefault("0");
        item.user_protected          = user_protectedElement->GetTextOrDefault("0");
        item.user_followers_count    = user_followers_countElement->GetTextOrDefault("0");

        container.push_back(item);
        entry++;
    }
  } catch(ticpp::Exception& ex) {
    mError = TE_PARSE_ERROR;
    LOG(LS_ERROR) << ex.what();
    return;
    }
}

std::vector<Wrapper::WrapperItem> Wrapper::Get(int get, const std::string page)
{
  mError = TE_WE_OK;
  container.clear();
  switch(get)
  {
    case PUBLIC_TIMELINE:

        Parse(HTTP_Dispatch(GET, "/statuses/public_timeline.xml", false, "NULL"));
        LOG(LS_INFO) << "Requesting public timetime";
        break;
    case FRIENDS_TIMELINE:
        Parse(HTTP_Dispatch(GET, "/statuses/friends_timeline.xml?page="+page, true, "NULL"));
        LOG(LS_INFO) << "Requesting friends timeline";
        break;
    case FRIENDS_SINCE:
        Parse(HTTP_Dispatch(GET, "/statuses/friends_timeline.xml?since="+page, true, "NULL"));
        LOG(LS_INFO) << "Requested friends timeline since " << page;
        break;
    case FRIENDS_SINCE_ID:
        Parse(HTTP_Dispatch(GET, "/statuses/friends_timeline.xml?since_id="+page, true, "NULL"));
        LOG(LS_INFO) << "Requested friends timeline since id " << page;
        break;
    case DIRECT_MESSAGE_GET:
        Parse(HTTP_Dispatch(GET, "/direct_messages.xml?page="+page, true, "NULL"));
        LOG(LS_INFO) << "Requested Direct Messages for page " << page;
        break;
    case DIRECT_MESSAGE_SENT:
        Parse(HTTP_Dispatch(GET, "/direct_messages/sent.xml?page="+page, true, "NULL"));
        LOG(LS_INFO) << "Requested Direct Messages for page " << page;
        break;
    case USER_TIMELINE:
        Parse(HTTP_Dispatch(GET, "/statuses/user_timeline/"+page+".xml", true, "NULL"));
        LOG(LS_INFO) << "Requesting Last 20 Twitts by User: " << page;
        break;
    default:
        mError = TE_INVALID_OPTION;
        LOG(LS_ERROR) << "Get() switch in wrapper hit the default";
        break;
  }
  return container;
}


void Wrapper::Send(int send, const std::string message)
{
  mError = TE_WE_OK; //initialize error value
  switch(send)
  {
    case NEW_STATUS:
      HTTP_Dispatch(POST, "/statuses/update.json", true, "status= " + message);
      LOG(LS_INFO) << "Posting New Tweet!";
      break;
    case ADD_FRIEND:
      HTTP_Dispatch(POST, "/friendships/create/"+message+".json?follow=true",true,"NULL");
      LOG(LS_INFO) << "Adding New Friend!";
      break;
    case DESTROY_FRIEND:
      HTTP_Dispatch(POST, "/friendships/destroy/"+message+".xml",true,"NULL");
      LOG(LS_INFO) << "Remove a Friend!";
      break;
    case DESTROY_STATUS:
      HTTP_Dispatch(POST, "/statuses/destroy/"+message+".xml",true,"NULL");
      LOG(LS_INFO) << "Removed a Status!";
      break;
    default:
      mError = TE_INVALID_OPTION;
      LOG(LS_ERROR) << "Invalid option";
      break;
  }
}

void Wrapper::Send_DM(const std::string recipient, const std::string message)
{
  mError = TE_WE_OK;
  HTTP_Dispatch(POST, "/direct_messages/new.xml?user="+recipient+"&text="+message, true, "NULL");
  LOG(LS_INFO) << "Sending Direct Message";
}

TweetxError Wrapper::Get_Error()
{
 return mError;
}


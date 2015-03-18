#summary how to set up SendSms plugin for tweetx
#labels Phase-Implementation

# Introduction #

How to set up `SendSms` for tweetx


# Details #
**Requirements:**
  * install **msmtp**
  * configure your email account for msmtp.
```
    touch ~/.msmtprc
    chmod 0600 ~/.msmtprc
```
> _sample .msmtprc file_
```
   amitesh@amitesh-laptop:~$ cat ~/.msmtprc 
   
   account gmail
   host smtp.gmail.com
   tls on
   tls_certcheck off
   port 587
   auth login
   from <your email id>@gmail.com
   user <email id> #without gmail.com
   password <passwd>
```

  * modify tweetx config file _~/.tweetx/config_

  1. adding msmtp command

> MSMTP\_COMMAND=msmtp -t -C <msmtp config file> -a <account name>
> > e.g.
> > MSMTP\_COMMAND=msmtp -t -C ~/.msmtprc -a gmail

  1. setting mobile number


> MOBILE\_NUMBER=<your mobile number@mobile service provider>
> > e.g.
> > MOBILE\_NUMBER=XXXXXXXXXXXXX@airtelap.com

  1. Setting timeout


> MSMTP\_TIMEOUT=<timeout time in seconds>
> > e.g.
> > MSMTP\_TIMEOUT=300


> _sample tweetx config file_
```
	  USERNAME=<twitter username>
		PASSWORD=<password>
		SSL_ENABLED=y
		HTTP_PROXY=
		HTTP_PROXY_PORT=
		HTTP_PROXY_USER=
		HTTP_PORT_PASSWORD=
		MSMTP_COMMAND=msmtp -t -C ~/.msmtprc -a gmail 
		MSMTP_TIMEOUT=30
		MOBILE_NUMBER=<your phone number@provider.com>
```
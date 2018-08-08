# DeLorean-Mail Datechanger  

Hello everyone! This is the magic email filter, that you need to use with postfix to change most of the dates in incoming and outgoing email.

It communicates with the dmail-connect client via localhost UDP on port 1337.  
You need to be running dmail-connect at all times to make this filter program work properly. It uses the time offset provided by dmail-connect to change the timestamps (by subtracting the amount of hours given)  
It communicates using the Future Gadget Protocol messages.  
```
FGP – Future Gadget Protocol  
REQTO : request current time offset  
RCVTO (int hours) : receive time offset (int hours)  
RCVOK : successfully received new offset  
MAILD : sent when mail processed  
ELPSY : used for connection keepalive  
KONGROO : used for connection keepalive
```

##Setup
Configure your postfix server like outlined on http://www.postfix.org/FILTER_README.html#simple_filter using the emailfilter.sh script provided here. Follow their instructions from `Once you're satisfied with the content filtering script:` onwards.

Turn on the filter for emails arriving via smtp (as demonstrated on the postfix website above), smtps and submission (comparable to how the smtp filter was set up in the instructions in the website above). Please edit the path to dmail-filter mentioned in emailfilter.sh according to your storage location!

####Setup example

For example, i added this to postfix's /etc/postfix/master.cf at the end:
```
dmail-filter     unix -       n       n       -       10      pipe
        flags=Rq user=filter null_sender=
        argv=/path/to/your/emailfilter.sh -f ${sender} -- {$recipient}
```
whilst adding a  
```         -o content_filter=dmail-filter:dummy```
under smtp, submission and smtps in master.cf.  

It may end up looking like this (an excerpt of my config): 
```
smtp      inet  n       -       y       -       -       smtpd
        -o content_filter=dmail-filter:dummy
submission inet n       -       y       -       -       smtpd
        -o content_filter=dmail-filter:dummy
        (some more -o's depending on your configuration here) 
smtps     inet  n       -       y       -       -       smtpd
        -o content_filter=dmail-filter:dummy
        (some more -o's depending on your configuration here)
```
Don't forget to restart/reload postfix afterwards!
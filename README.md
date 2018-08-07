# DeLorean-Mail Datechanger  

Hello everyone! This is the magic email filter, that you need to use with postfix to change most of the dates in incoming and outgoing email.

It communicates with the dmail-connect client via localhost UDP on port 1337.  
You need to be running dmail-connect at all times to make this filter program work properly. It uses the time offset provided by dmail-connect to change the timestamps (by subtracting the amount of hours given)  
It communicates using the Future Gadget Protocol messages.  

Configure your postfix server like outlined on http://www.postfix.org/FILTER_README.html#simple_filter using the emailfilter.sh script provided here. Turn on the filter for emails arriving via smtp, smtps and submission.

FGP – Future Gadget Protocol
REQTO : request current time offset  
RCVTO (int hours) : receive time offset (int hours)  
RCVOK : successfully received new offset  
MAILD : sent when mail processed  
ELPSY : used for connection keepalive  
KONGROO : used for connection keepalive
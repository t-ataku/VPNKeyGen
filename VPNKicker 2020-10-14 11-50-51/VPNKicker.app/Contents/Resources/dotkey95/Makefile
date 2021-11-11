#SRCS=Dotkey95.c md4.c md5c.c otp_hash.c otp_put.c prefs.c sha.c tray.c
#SRCS=md4.c md5c.c otp_hash.c otp_put.c prefs.c sha.c tray.c
#SRCS=md4.c md5c.c otp_hash.c otp_put.c sha.c tray.c
SRCS=dotkeyux.c md4.c md5c.c otp_hash.c otp_put.c sha.c
OBJS=$(SRCS:.c=.o)
CDEFFLAGS=-DUSE_STDLIB_H -DUSE_STRINGS_H -DUSE_STRING_H

.c.o:
	cc -c -g $(CDEFFLAGS) $<

all: dotkey95
	echo $(SRCS)
	echo $(OBJS)

clean:
	rm -f dotkey95 $(OBJS)

dotkey95: $(OBJS)
	cc -g -o dotkey95 $(OBJS)

CC     = cc
CFLAGS = -Wall -O2 -Wextra
prefix = /usr/local
PREFIX = $(prefix)

writelines:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) writelines.c -o writelines

install: writelines
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mv -f writelines $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/writelines

clean:
	rm -f writelines

.PHONY: writelines install uninstall clean

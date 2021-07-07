A mirror of GASP -- the asm preprocessor
========================================

Have you ever wanted to just expand macros of GNU as (gas)? It was possible in the days of old. All you need is [``gasp``](https://nixdoc.net/man-pages/Linux/man1/gasp.1.html).

This repo contains the last version of GNU binutils, that contained the *gasp* binary. In order to get that beloved bin, run in the main dir:

```bash
./configure
cd bfd
make
cd ../libiberty/
make
cd ../gas
make gasp-new
```

The result will be placed in ``gas/gasp-new``. Finally, take a look at the [man page](https://nixdoc.net/man-pages/Linux/man1/gasp.1.html) or the [reference manual](https://github.com/matrach/gasp/raw/master/gasp.pdf) and party like it's 1999.

[![Get it, get it, like 1999](http://img.youtube.com/vi/NbqtAuT4zbk/0.jpg)](http://www.youtube.com/watch?v=NbqtAuT4zbk)

Footnote: gasp wasn't compiling on the source commit by default, so I hacked the makefiles a bit, therefore don't expect ``as`` to work. Also, don't expect it to parse anything remotely recent.

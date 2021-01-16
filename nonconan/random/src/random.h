#ifndef _random_h_
#define _random_h_

/**
 * Returns a standard IEEE-vetted random number (RFC 1149.5)
 *
 * @see [**Random Number** on _xkcd.com_](https://xkcd.com/221/)
 * @see [**221: Random Number** on _explainxkcd.com_](https://www.explainxkcd.com/wiki/index.php/221:_Random_Number)
 */
#if defined(_WIN32) || defined(__CYGWIN__)
extern int __declspec(dllexport) getRandomNumber();
#else
extern int getRandomNumber();
#endif // defined(_WIN32) || defined(__CYGWIN__)

#endif // _random_h_

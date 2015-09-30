# Introduction #

På denna sida följer lite Dos and Dont's när man programmerar för verkstan.


# Details #

**I managed C++ skall alltid rena C++-headers inkluderas före managed C++-headers. Detta gäller även i cpp-filer!** Varför? Jo, det är viktigt att vanilla-C++-filer med eventuella inkluderingar av Windows headers hamnar först, annars kan konflikter mellan vanilla-C++ och managed-C++ uppkomma som resulterar i kryptiska kompileringsfel.
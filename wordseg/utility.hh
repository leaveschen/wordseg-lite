//
// Created by c on 26/07/2017 10:40 AM
//

#ifndef WORDSEG_UTILITY_HH
#define WORDSEG_UTILITY_HH

/* include section */

/* class & function section */

#define DISALLOW_COPY(TypeName) \
	TypeName(TypeName const&) = delete; \
	TypeName& operator=(TypeName const&) = delete;

#define DISALLOW_MOVE(TypeName) \
	TypeName(TypeName&&) = delete; \
	TypeName& operator=(TypeName&&) = delete;


#endif// WORDSEG_UTILITY_HH



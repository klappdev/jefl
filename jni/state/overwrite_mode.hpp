#ifndef JNI_STATE_OVERWRITE_MODE_HPP_
#define JNI_STATE_OVERWRITE_MODE_HPP_

namespace kl {
	enum class overwrite_mode {
		SIMPLE_MODE  = 1,
		DOE_MODE     = 3,
		OPENBSD_MODE = 4,
		RCMP_MODE    = 5,
		DOD_MODE     = 7,
		GUTMAN_MODE  = 35
	};
}



#endif /* JNI_STATE_OVERWRITE_MODE_HPP_ */

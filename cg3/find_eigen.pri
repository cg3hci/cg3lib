#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

EIGEN_ENV_VARIABLE = $$(EIGEN_HOME)

isEmpty(EIGEN_PATH):!isEmpty(EIGEN_ENV_VARIABLE):exists($$EIGEN_ENV_VARIABLE) {
	EIGEN_PATH = $$EIGEN_ENV_VARIABLE
}

!isEmpty(EIGEN_PATH):exists($$EIGEN_PATH) {
	INCLUDEPATH += -I $$EIGEN_PATH
}
else {
	unix{
		exists(/usr/include/eigen3){ #linux apt default
			INCLUDEPATH += -I /usr/include/eigen3
		}
		else{
			exists(/usr/local/include/eigen3){ #mac brew default
				INCLUDEPATH += -I /usr/local/include/eigen3/
			}
			else {
				error(Eigen required and not found.)
			}
		}
	}

	win32 {
		exists(C:/libs/eigen3){
			INCLUDEPATH += -I "C:/libs/eigen3"
			EIGEN_PATH = C:/libs/eigen3
		}
		else{
			error(Eigen required and not found.)
		}
	}
}

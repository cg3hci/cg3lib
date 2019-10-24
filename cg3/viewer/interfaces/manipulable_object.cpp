/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "manipulable_object.h"
#include <cg3/geometry/transformations3.h>

namespace cg3 {

CG3_INLINE ManipulableObject::ManipulableObject() : ManipulableObject(0.7)
{
}

CG3_INLINE ManipulableObject::ManipulableObject(double grabbingFactor) :
    axis(false),
	_keepsGrabbingMouse(false),
    gf(grabbingFactor)
{
    setSpinningSensitivity(100.0);
}

CG3_INLINE bool ManipulableObject::drawRelativeAxis() const
{
    return axis;
}

CG3_INLINE void ManipulableObject::setDrawRelativeAxis(bool b) const
{
	axis = b;
}

CG3_INLINE void ManipulableObject::setPosition(const Point3d &pos)
{
	ManipulatedFrame::setPosition(qglviewer::Vec(pos.x(), pos.y(), pos.z()));
}

CG3_INLINE void ManipulableObject::setTranslation(const Point3d &pos)
{
	ManipulatedFrame::setTranslation(qglviewer::Vec(pos.x(), pos.y(), pos.z()));
}

CG3_INLINE const double* ManipulableObject::matrix() const
{
    return ManipulatedFrame::matrix();
}

/**
 * @brief ManipulableObject::position
 * @return the position of the center of the object Frame in
 * absolute position
 */
CG3_INLINE Point3d ManipulableObject::position() const
{
    qglviewer::Vec p(ManipulatedFrame::position());
	return Point3d(p.x, p.y, p.z);
}

/**
 * @brief ManipulableObject::translation
 * @return the position of the center of the object Frame in
 * relative position with respect of the reference Frame.
 */
CG3_INLINE Point3d ManipulableObject::translation() const
{
	qglviewer::Vec p(ManipulatedFrame::translation());
	return Point3d(p.x, p.y, p.z);
}

CG3_INLINE bool ManipulableObject::grabsMouse() const
{
	return ManipulatedFrame::grabsMouse();
}

CG3_INLINE bool ManipulableObject::keepsGrabbingMouse() const
{
	return _keepsGrabbingMouse;
}

CG3_INLINE void ManipulableObject::setGrabbingFactor(double gf)
{
    this->gf = gf;
}

CG3_INLINE double ManipulableObject::grabbingFactor() const
{
	return gf;
}

CG3_INLINE void ManipulableObject::rotationMatrix(double m[][3]) const
{
	qglviewer::Vec axis = orientation().axis();
	double angle = orientation().angle();
	if (angle == 0){
		for (uint i = 0; i < 3; i++){
			for (uint j = 0; j < 3; j++){
				if (i==j)
					m[i][j] = 1;
				else
					m[i][j] = 0;
			}
		}
	}
	else
		cg3::rotationMatrix(cg3::Vec3d(axis.x, axis.y, axis.z), angle, m);
}

CG3_INLINE void ManipulableObject::resetRotation()
{
	setRotation(qglviewer::Quaternion(0,0,0,1));
}

#ifdef CG3_WITH_EIGEN
CG3_INLINE void ManipulableObject::rotationMatrix(Eigen::Matrix3d &m) const
{
	qglviewer::Vec axis = orientation().axis();
	double angle = orientation().angle();
	if (angle == 0)
		m = Eigen::Matrix3d::Identity();
	else
		cg3::rotationMatrix(cg3::Vec3d(axis.x, axis.y, axis.z), angle, m);
}

CG3_INLINE Eigen::Matrix3d ManipulableObject::rotationMatrix() const
{
	qglviewer::Vec axis = orientation().axis();
	double angle = orientation().angle();
	if (angle == 0)
		return  Eigen::Matrix3d::Identity();
	return cg3::rotationMatrix(cg3::Vec3d(axis.x, axis.y, axis.z), angle);
}
#endif //CG3_WITH_EIGEN

CG3_INLINE void ManipulableObject::checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera)
{
	qglviewer::Vec center(sceneCenter().x(), sceneCenter().y(), sceneCenter().z());
    const qglviewer::Quaternion qt = rotation();
    center = qt.rotate(center);
    const qglviewer::Vec extreme(center.x + sceneRadius(), center.y + sceneRadius(), center.z + sceneRadius());
    const qglviewer::Vec pos(position().x(), position().y(), position().z());
    const qglviewer::Vec proj = camera->projectedCoordinatesOf(pos + center);
    const qglviewer::Vec projex = camera->projectedCoordinatesOf(pos + extreme);
    const int threshold = std::sqrt ( std::pow((proj.x - projex.x), 2) +
                                std::pow((proj.y - projex.y), 2) ) * gf;
	setGrabsMouse(_keepsGrabbingMouse || ((fabs(x - proj.x) < threshold) && (fabs(y - proj.y) < threshold)));
}

CG3_INLINE void ManipulableObject::mousePressEvent(QMouseEvent* const event, qglviewer::Camera* const camera)
{
    ManipulatedFrame::mousePressEvent(event, camera);
    if (grabsMouse())
		_keepsGrabbingMouse = true;
}

CG3_INLINE void ManipulableObject::mouseReleaseEvent(QMouseEvent* const event, qglviewer::Camera* const camera)
{
    ManipulatedFrame::mouseReleaseEvent(event, camera);
	_keepsGrabbingMouse = false;
}

} //namespace cg3

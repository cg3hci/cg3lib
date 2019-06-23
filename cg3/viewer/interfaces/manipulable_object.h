/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_MANIPULABLE_OBJECT_H
#define CG3_MANIPULABLE_OBJECT_H

#include <cg3/geometry/bounding_box3.h>

#include <QGLViewer/manipulatedFrame.h>
#include <cg3/viewer/interfaces/drawable_object.h>

namespace cg3 {

class ManipulableObject : public virtual DrawableObject, public qglviewer::ManipulatedFrame
{
public:
    ManipulableObject();
    ManipulableObject(double grabbingFactor);
    virtual ~ManipulableObject() {}

    virtual void drawHighlighted() const = 0;

    virtual bool drawRelativeAxis() const;

    virtual void setDrawRelativeAxis(bool b = true) const;

	virtual void setPosition(const cg3::Point3d& pos);

	virtual void setTranslation(const cg3::Point3d& pos);

    virtual const double* matrix() const;

    virtual Point3d position() const;

	virtual Point3d translation() const;

    virtual bool grabsMouse() const;

	virtual bool keepsGrabbingMouse() const;

    virtual void setGrabbingFactor(double gf);

    virtual double grabbingFactor() const;

	virtual void rotationMatrix(double m[][3]) const;

	virtual void resetRotation();

#ifdef CG3_WITH_EIGEN
	void rotationMatrix(Eigen::Matrix3d& m) const;
	Eigen::Matrix3d rotationMatrix() const;
#endif //CG3_WITH_EIGEN

    // MouseGrabber interface
    virtual void checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera);

protected:
    void mousePressEvent(QMouseEvent *const event, qglviewer::Camera *const camera);
    void mouseReleaseEvent(QMouseEvent *const event, qglviewer::Camera *const camera);

private:
    mutable bool axis;
	bool _keepsGrabbingMouse;
    double gf;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_MANIPULABLE_OBJECT_CPP "manipulable_object.cpp"
#include CG3_MANIPULABLE_OBJECT_CPP
#undef CG3_MANIPULABLE_OBJECT_CPP
#endif //CG3_STATIC

#endif // CG3_MANIPULABLE_OBJECT_H

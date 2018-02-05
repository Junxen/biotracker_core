#pragma once

#include "Interfaces/IView/IViewTrackedComponent.h"
#include <cv.h>

class AreaDescriptor : public QObject, public IView, public QGraphicsItem
{
    Q_OBJECT
public:
    AreaDescriptor(IController *controller, IModel *model) :
		IView(controller, model) {};
	~AreaDescriptor();

	virtual void setBrush(QBrush brush) = 0;
	virtual void setRect(std::vector<cv::Point> rect) = 0;
	virtual std::vector<cv::Point> getRect() = 0;
	virtual void updateRect() = 0;

    void setDimensions(int x, int y) {
        _vdimX = x;
        _vdimY = y;
    }
protected:

    int _vdimX = 1;
    int _vdimY = 1;
};


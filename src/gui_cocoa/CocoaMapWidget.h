#import <Cocoa/Cocoa.h>
#import "MapView.h"

#include "game/gui/map_widget.h"

class CocoaMapWidget: public aw::gui::map_widget {
public:
	typedef boost::shared_ptr<CocoaMapWidget> ptr;
	
	CocoaMapWidget(MapView* mView) {
		mapView = mView;
	}
	
	~CocoaMapWidget() {
		[mapView release];
	}
	
	void setView(MapView* mView) {
		[mView retain];
		[mapView release];
		mapView = mView;
	}
	
	virtual void queue_draw();
	
	virtual void disable();     
	virtual void enable(); 
	
private:
	MapView* mapView;
};

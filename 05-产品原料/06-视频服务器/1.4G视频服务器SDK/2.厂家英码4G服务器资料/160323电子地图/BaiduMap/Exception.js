/**
 *	异常
 *	
 *	X--- : 1、Map;	2、Marker;	3、Polyline;
 *	
 *	-X-- : 1、参数错误	2、API调用异常
 *
 *	--X- : 1、创建时 2、更新时	3、其他操作
 *	
 *	ERROR:
 *	2111:Marker创建时Json解析异常
 *	2112:Marker创建时key已存在
 *  2211:Marker创建时API调用异常
 *	2121:Marker修改时Json解析异常
 *  2122:Marker修改属性时key不存在
 *	2131:Marker显示标记时key不存在
 *	2132:Marker隐藏标记时key不存在
 *	2133:Marker定位时key不存在
 *	2134:Marker定位时marker未加入地图或在地图上不显示
 *	2135:Marker跟踪时key不存在
 *	
 *	3111:Polyline创建时Json解析异常
 *	3112:Polyline创建时key已存在
 *  3211:Polyline创建时API调用异常
 *	3121:Polyline修改时Json解析异常
 *  3122:Polyline修改属性时key不存在
 *	3131:Polyline显示标记时key不存在
 *	3132:Polyline隐藏标记时key不存在
 **/



function baiduMapException(code, e, param) {
	var name = "";
	var message = "";
	if(e != null) {
		name = e.name;
		message = e.message;
	}
	window.external.baiduMapException(code, name, message, param);
}
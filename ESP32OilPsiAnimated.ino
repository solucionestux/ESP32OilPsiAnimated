//128*64 (double height of brz gauge)
//i2c interface
//not sure what to use wifi for (webserve it with wifi direct webpage?)

//this uses the squix ssd1306 library...it is faster and has more functions
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"
#include "SSD1306Brzo.h"
// Include the UI lib
#include "OLEDDisplayUi.h"
#include "WiFi.h"
#include "ESPmDNS.h" //so you can got to gaugename.localhost

//webserver stuff
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Include custom images
#include "images.h"
int atmo = 0;
SSD1306  display(0x3c, 4, 15); //for the heltec with the built in oled...SSD1306  display(0x3c, D3, D5); for normal
int rPSI = 0;
bool isInverted = false;
int peakPSI = 0;
String Soilpsi = "";

const char *ssid = "oil_psi_gauge_ap";
const char *password = "password";

AsyncWebServer server(80);

void setup() {
  //pinMode(36, INPUT);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 to high
  //Wire.begin(4,15);

  display.init();

  //display.flipScreenVertically(); //usb to the left
  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  //ui.setTargetFPS(30);
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  //show logo
  //display.drawFastImage(59, 21, splash_Logo_width, splash_Logo_height, splash_Logo_bits);
  //display.drawXbm(0,0, splash_Logo_width, splash_Logo_height, splash_Logo_bits);
  //display.display();
  //delay(2000);
  //do the gauge sweep dance
  display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge0_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge1_width, gauge1_height, gauge1_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge2_width, gauge2_height, gauge2_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge3_width, gauge3_height, gauge3_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge4_width, gauge4_height, gauge4_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge5_width, gauge5_height, gauge5_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge6_width, gauge6_height, gauge6_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge7_width, gauge7_height, gauge7_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge8_width, gauge8_height, gauge8_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge9_width, gauge9_height, gauge9_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge10_width, gauge10_height, gauge10_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge11_width, gauge11_height, gauge11_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge12_width, gauge12_height, gauge12_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge13_width, gauge13_height, gauge13_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge14_width, gauge14_height, gauge14_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge15_width, gauge15_height, gauge15_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge16_width, gauge16_height, gauge16_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge17_width, gauge17_height, gauge17_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge18_width, gauge18_height, gauge18_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge19_width, gauge19_height, gauge19_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge20_width, gauge20_height, gauge20_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge19_width, gauge19_height, gauge19_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge18_width, gauge18_height, gauge18_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge17_width, gauge17_height, gauge17_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge16_width, gauge16_height, gauge16_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge15_width, gauge15_height, gauge15_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge14_width, gauge14_height, gauge14_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge13_width, gauge13_height, gauge13_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge12_width, gauge12_height, gauge12_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge11_width, gauge11_height, gauge11_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge10_width, gauge10_height, gauge10_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge9_width, gauge9_height, gauge9_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge8_width, gauge8_height, gauge8_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge7_width, gauge7_height, gauge7_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge6_width, gauge6_height, gauge6_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge5_width, gauge5_height, gauge5_bits);
  display.display();
  delay(20);
  display.clear();
  display.drawXbm(0, 0, gauge4_width, gauge4_height, gauge4_bits);
  display.display();
  delay(30);
  display.clear();
  display.drawXbm(0, 0, gauge3_width, gauge3_height, gauge3_bits);
  display.display();
  delay(40);
  display.clear();
  display.drawXbm(0, 0, gauge2_width, gauge2_height, gauge2_bits);
  display.display();
  delay(50);
  display.clear();
  display.drawXbm(0, 0, gauge1_width, gauge1_height, gauge1_bits);
  display.display();
  delay(50);
  display.clear();
  display.clear();
  Serial.begin(9600);

  MDNS.begin("oilpsigauge");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<!DOCTYPE html><html lang=\"en-US\"><head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head><body><canvas id=\"smoothie-chart\" width=\"570\" height=\"150\"/><div id=currentVal></div><script>(function(exports){Date.now=Date.now || function(){return new Date().getTime();}; var Util={extend: function(){arguments[0]=arguments[0] ||{}; for (var i=1; i < arguments.length; i++){for (var key in arguments[i]){if (arguments[i].hasOwnProperty(key)){if (typeof(arguments[i][key])==='object'){if (arguments[i][key] instanceof Array){arguments[0][key]=arguments[i][key];}else{arguments[0][key]=Util.extend(arguments[0][key], arguments[i][key]);}}else{arguments[0][key]=arguments[i][key];}}}}return arguments[0];}, binarySearch: function(data, value){var low=0, high=data.length; while (low < high){var mid=(low + high) >> 1; if (value < data[mid][0]) high=mid; else low=mid + 1;}return low;}}; function TimeSeries(options){this.options=Util.extend({}, TimeSeries.defaultOptions, options); this.disabled=false; this.clear();}TimeSeries.defaultOptions={resetBoundsInterval: 3000, resetBounds: true}; TimeSeries.prototype.clear=function(){this.data=[]; this.maxValue=Number.NaN; this.minValue=Number.NaN;}; TimeSeries.prototype.resetBounds=function(){if (this.data.length){this.maxValue=this.data[0][1]; this.minValue=this.data[0][1]; for (var i=1; i < this.data.length; i++){var value=this.data[i][1]; if (value > this.maxValue){this.maxValue=value;}if (value < this.minValue){this.minValue=value;}}}else{this.maxValue=Number.NaN; this.minValue=Number.NaN;}}; TimeSeries.prototype.append=function(timestamp, value, sumRepeatedTimeStampValues){var i=this.data.length - 1; while (i >=0 && this.data[i][0] > timestamp){i--;}if (i===-1){this.data.splice(0, 0, [timestamp, value]);}else if (this.data.length > 0 && this.data[i][0]===timestamp){if (sumRepeatedTimeStampValues){this.data[i][1] +=value; value=this.data[i][1];}else{this.data[i][1]=value;}}else if (i < this.data.length - 1){this.data.splice(i + 1, 0, [timestamp, value]);}else{this.data.push([timestamp, value]);}this.maxValue=isNaN(this.maxValue) ? value : Math.max(this.maxValue, value); this.minValue=isNaN(this.minValue) ? value : Math.min(this.minValue, value);}; TimeSeries.prototype.dropOldData=function(oldestValidTime, maxDataSetLength){var removeCount=0; while (this.data.length - removeCount >=maxDataSetLength && this.data[removeCount + 1][0] < oldestValidTime){removeCount++;}if (removeCount !==0){this.data.splice(0, removeCount);}}; function SmoothieChart(options){this.options=Util.extend({}, SmoothieChart.defaultChartOptions, options); this.seriesSet=[]; this.currentValueRange=1; this.currentVisMinValue=0; this.lastRenderTimeMillis=0; this.lastChartTimestamp=0; this.mousemove=this.mousemove.bind(this); this.mouseout=this.mouseout.bind(this);}SmoothieChart.tooltipFormatter=function (timestamp, data){var timestampFormatter=this.options.timestampFormatter || SmoothieChart.timeFormatter, lines=[timestampFormatter(new Date(timestamp))]; for (var i=0; i < data.length; ++i){lines.push('<span style=\"color:' + data[i].series.options.strokeStyle + '\">' + this.options.yMaxFormatter(data[i].value, this.options.labels.precision) + '</span>');}return lines.join('<br>');}; SmoothieChart.defaultChartOptions={millisPerPixel: 20, enableDpiScaling: true, yMinFormatter: function(min, precision){return parseFloat(min).toFixed(precision);}, yMaxFormatter: function(max, precision){return parseFloat(max).toFixed(precision);}, yIntermediateFormatter: function(intermediate, precision){return parseFloat(intermediate).toFixed(precision);}, maxValueScale: 1, minValueScale: 1, interpolation: 'bezier', scaleSmoothing: 0.125, maxDataSetLength: 2, scrollBackwards: false, displayDataFromPercentile: 1, grid:{fillStyle: '#000000', strokeStyle: '#777777', lineWidth: 1, sharpLines: false, millisPerLine: 1000, verticalSections: 2, borderVisible: true}, labels:{fillStyle: '#ffffff', disabled: false, fontSize: 10, fontFamily: 'monospace', precision: 2, showIntermediateLabels: false, intermediateLabelSameAxis: true,}, horizontalLines: [], tooltip: false, tooltipLine:{lineWidth: 1, strokeStyle: '#BBBBBB'}, tooltipFormatter: SmoothieChart.tooltipFormatter, nonRealtimeData: false, responsive: false, limitFPS: 0}; SmoothieChart.AnimateCompatibility=(function(){var requestAnimationFrame=function(callback, element){var requestAnimationFrame=window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame || function(callback){return window.setTimeout(function(){callback(Date.now());}, 16);}; return requestAnimationFrame.call(window, callback, element);}, cancelAnimationFrame=function(id){var cancelAnimationFrame=window.cancelAnimationFrame || function(id){clearTimeout(id);}; return cancelAnimationFrame.call(window, id);}; return{requestAnimationFrame: requestAnimationFrame, cancelAnimationFrame: cancelAnimationFrame};})(); SmoothieChart.defaultSeriesPresentationOptions={lineWidth: 1, strokeStyle: '#ffffff'}; SmoothieChart.prototype.addTimeSeries=function(timeSeries, options){this.seriesSet.push({timeSeries: timeSeries, options: Util.extend({}, SmoothieChart.defaultSeriesPresentationOptions, options)}); if (timeSeries.options.resetBounds && timeSeries.options.resetBoundsInterval > 0){timeSeries.resetBoundsTimerId=setInterval( function(){timeSeries.resetBounds();}, timeSeries.options.resetBoundsInterval );}}; SmoothieChart.prototype.removeTimeSeries=function(timeSeries){var numSeries=this.seriesSet.length; for (var i=0; i < numSeries; i++){if (this.seriesSet[i].timeSeries===timeSeries){this.seriesSet.splice(i, 1); break;}}if (timeSeries.resetBoundsTimerId){clearInterval(timeSeries.resetBoundsTimerId);}}; SmoothieChart.prototype.getTimeSeriesOptions=function(timeSeries){var numSeries=this.seriesSet.length; for (var i=0; i < numSeries; i++){if (this.seriesSet[i].timeSeries===timeSeries){return this.seriesSet[i].options;}}}; SmoothieChart.prototype.bringToFront=function(timeSeries){var numSeries=this.seriesSet.length; for (var i=0; i < numSeries; i++){if (this.seriesSet[i].timeSeries===timeSeries){var set=this.seriesSet.splice(i, 1); this.seriesSet.push(set[0]); break;}}}; SmoothieChart.prototype.streamTo=function(canvas, delayMillis){this.canvas=canvas; this.delay=delayMillis; this.start();}; SmoothieChart.prototype.getTooltipEl=function (){if (!this.tooltipEl){this.tooltipEl=document.createElement('div'); this.tooltipEl.className='smoothie-chart-tooltip'; this.tooltipEl.style.position='absolute'; this.tooltipEl.style.display='none'; document.body.appendChild(this.tooltipEl);}return this.tooltipEl;}; SmoothieChart.prototype.updateTooltip=function (){var el=this.getTooltipEl(); if (!this.mouseover || !this.options.tooltip){el.style.display='none'; return;}var time=this.lastChartTimestamp; var t=this.options.scrollBackwards ? time - this.mouseX * this.options.millisPerPixel : time - (this.canvas.offsetWidth - this.mouseX) * this.options.millisPerPixel; var data=[]; for (var d=0; d < this.seriesSet.length; d++){var timeSeries=this.seriesSet[d].timeSeries; if (timeSeries.disabled){continue;}var closeIdx=Util.binarySearch(timeSeries.data, t); if (closeIdx > 0 && closeIdx < timeSeries.data.length){data.push({series: this.seriesSet[d], index: closeIdx, value: timeSeries.data[closeIdx][1]});}}if (data.length){el.innerHTML=this.options.tooltipFormatter.call(this, t, data); el.style.display='block';}else{el.style.display='none';}}; SmoothieChart.prototype.mousemove=function (evt){this.mouseover=true; this.mouseX=evt.offsetX; this.mouseY=evt.offsetY; this.mousePageX=evt.pageX; this.mousePageY=evt.pageY; var el=this.getTooltipEl(); el.style.top=Math.round(this.mousePageY) + 'px'; el.style.left=Math.round(this.mousePageX) + 'px'; this.updateTooltip();}; SmoothieChart.prototype.mouseout=function (){this.mouseover=false; this.mouseX=this.mouseY=-1; if (this.tooltipEl) this.tooltipEl.style.display='none';}; SmoothieChart.prototype.resize=function (){var dpr=!this.options.enableDpiScaling || !window ? 1 : window.devicePixelRatio, width, height; if (this.options.responsive){width=this.canvas.offsetWidth; height=this.canvas.offsetHeight; if (width !==this.lastWidth){this.lastWidth=width; this.canvas.setAttribute('width', (Math.floor(width * dpr)).toString());}if (height !==this.lastHeight){this.lastHeight=height; this.canvas.setAttribute('height', (Math.floor(height * dpr)).toString());}}else if (dpr !==1){width=parseInt(this.canvas.getAttribute('width')); height=parseInt(this.canvas.getAttribute('height')); if (!this.originalWidth || (Math.floor(this.originalWidth * dpr) !==width)){this.originalWidth=width; this.canvas.setAttribute('width', (Math.floor(width * dpr)).toString()); this.canvas.style.width=width + 'px'; this.canvas.getContext('2d').scale(dpr, dpr);}if (!this.originalHeight || (Math.floor(this.originalHeight * dpr) !==height)){this.originalHeight=height; this.canvas.setAttribute('height', (Math.floor(height * dpr)).toString()); this.canvas.style.height=height + 'px'; this.canvas.getContext('2d').scale(dpr, dpr);}}}; SmoothieChart.prototype.start=function(){if (this.frame){return;}this.canvas.addEventListener('mousemove', this.mousemove); this.canvas.addEventListener('mouseout', this.mouseout); var animate=function(){this.frame=SmoothieChart.AnimateCompatibility.requestAnimationFrame(function(){if(this.options.nonRealtimeData){var dateZero=new Date(0); var maxTimeStamp=this.seriesSet.reduce(function(max, series){var dataSet=series.timeSeries.data; var indexToCheck=Math.round(this.options.displayDataFromPercentile * dataSet.length) - 1; indexToCheck=indexToCheck >=0 ? indexToCheck : 0; indexToCheck=indexToCheck <=dataSet.length -1 ? indexToCheck : dataSet.length -1; if(dataSet && dataSet.length > 0){var lastDataTimeStamp=dataSet[indexToCheck][0]; max=max > lastDataTimeStamp ? max : lastDataTimeStamp;}return max;}.bind(this), dateZero); this.render(this.canvas, maxTimeStamp > dateZero ? maxTimeStamp : null);}else{this.render();}animate();}.bind(this));}.bind(this); animate();}; SmoothieChart.prototype.stop=function(){if (this.frame){SmoothieChart.AnimateCompatibility.cancelAnimationFrame(this.frame); delete this.frame; this.canvas.removeEventListener('mousemove', this.mousemove); this.canvas.removeEventListener('mouseout', this.mouseout);}}; SmoothieChart.prototype.updateValueRange=function(){var chartOptions=this.options, chartMaxValue=Number.NaN, chartMinValue=Number.NaN; for (var d=0; d < this.seriesSet.length; d++){var timeSeries=this.seriesSet[d].timeSeries; if (timeSeries.disabled){continue;}if (!isNaN(timeSeries.maxValue)){chartMaxValue=!isNaN(chartMaxValue) ? Math.max(chartMaxValue, timeSeries.maxValue) : timeSeries.maxValue;}if (!isNaN(timeSeries.minValue)){chartMinValue=!isNaN(chartMinValue) ? Math.min(chartMinValue, timeSeries.minValue) : timeSeries.minValue;}}if (chartOptions.maxValue !=null){chartMaxValue=chartOptions.maxValue;}else{chartMaxValue *=chartOptions.maxValueScale;}if (chartOptions.minValue !=null){chartMinValue=chartOptions.minValue;}else{chartMinValue -=Math.abs(chartMinValue * chartOptions.minValueScale - chartMinValue);}if (this.options.yRangeFunction){var range=this.options.yRangeFunction({min: chartMinValue, max: chartMaxValue}); chartMinValue=range.min; chartMaxValue=range.max;}if (!isNaN(chartMaxValue) && !isNaN(chartMinValue)){var targetValueRange=chartMaxValue - chartMinValue; var valueRangeDiff=(targetValueRange - this.currentValueRange); var minValueDiff=(chartMinValue - this.currentVisMinValue); this.isAnimatingScale=Math.abs(valueRangeDiff) > 0.1 || Math.abs(minValueDiff) > 0.1; this.currentValueRange +=chartOptions.scaleSmoothing * valueRangeDiff; this.currentVisMinValue +=chartOptions.scaleSmoothing * minValueDiff;}this.valueRange={min: chartMinValue, max: chartMaxValue};}; SmoothieChart.prototype.render=function(canvas, time){var nowMillis=Date.now(); if (this.options.limitFPS > 0 && nowMillis - this.lastRenderTimeMillis < (1000/this.options.limitFPS)) return; if (!this.isAnimatingScale){var maxIdleMillis=Math.min(1000/6, this.options.millisPerPixel); if (nowMillis - this.lastRenderTimeMillis < maxIdleMillis){return;}}this.resize(); this.updateTooltip(); this.lastRenderTimeMillis=nowMillis; canvas=canvas || this.canvas; time=time || nowMillis - (this.delay || 0); time -=time % this.options.millisPerPixel; this.lastChartTimestamp=time; var context=canvas.getContext('2d'), chartOptions=this.options, dimensions={top: 0, left: 0, width: canvas.clientWidth, height: canvas.clientHeight}, oldestValidTime=time - (dimensions.width * chartOptions.millisPerPixel), valueToYPixel=function(value){var offset=value - this.currentVisMinValue; return this.currentValueRange===0 ? dimensions.height : dimensions.height - (Math.round((offset / this.currentValueRange) * dimensions.height));}.bind(this), timeToXPixel=function(t){if(chartOptions.scrollBackwards){return Math.round((time - t) / chartOptions.millisPerPixel);}return Math.round(dimensions.width - ((time - t) / chartOptions.millisPerPixel));}; this.updateValueRange(); context.font=chartOptions.labels.fontSize + 'px ' + chartOptions.labels.fontFamily; context.save(); context.translate(dimensions.left, dimensions.top); context.beginPath(); context.rect(0, 0, dimensions.width, dimensions.height); context.clip(); context.save(); context.fillStyle=chartOptions.grid.fillStyle; context.clearRect(0, 0, dimensions.width, dimensions.height); context.fillRect(0, 0, dimensions.width, dimensions.height); context.restore(); context.save(); context.lineWidth=chartOptions.grid.lineWidth; context.strokeStyle=chartOptions.grid.strokeStyle; if (chartOptions.grid.millisPerLine > 0){context.beginPath(); for (var t=time - (time % chartOptions.grid.millisPerLine); t >=oldestValidTime; t -=chartOptions.grid.millisPerLine){var gx=timeToXPixel(t); if (chartOptions.grid.sharpLines){gx -=0.5;}context.moveTo(gx, 0); context.lineTo(gx, dimensions.height);}context.stroke(); context.closePath();}for (var v=1; v < chartOptions.grid.verticalSections; v++){var gy=Math.round(v * dimensions.height / chartOptions.grid.verticalSections); if (chartOptions.grid.sharpLines){gy -=0.5;}context.beginPath(); context.moveTo(0, gy); context.lineTo(dimensions.width, gy); context.stroke(); context.closePath();}if (chartOptions.grid.borderVisible){context.beginPath(); context.strokeRect(0, 0, dimensions.width, dimensions.height); context.closePath();}context.restore(); if (chartOptions.horizontalLines && chartOptions.horizontalLines.length){for (var hl=0; hl < chartOptions.horizontalLines.length; hl++){var line=chartOptions.horizontalLines[hl], hly=Math.round(valueToYPixel(line.value)) - 0.5; context.strokeStyle=line.color || '#ffffff'; context.lineWidth=line.lineWidth || 1; context.beginPath(); context.moveTo(0, hly); context.lineTo(dimensions.width, hly); context.stroke(); context.closePath();}}for (var d=0; d < this.seriesSet.length; d++){context.save(); var timeSeries=this.seriesSet[d].timeSeries; if (timeSeries.disabled){continue;}var dataSet=timeSeries.data, seriesOptions=this.seriesSet[d].options; timeSeries.dropOldData(oldestValidTime, chartOptions.maxDataSetLength); context.lineWidth=seriesOptions.lineWidth; context.strokeStyle=seriesOptions.strokeStyle; context.beginPath(); var firstX=0, lastX=0, lastY=0; for (var i=0; i < dataSet.length && dataSet.length !==1; i++){var x=timeToXPixel(dataSet[i][0]), y=valueToYPixel(dataSet[i][1]); if (i===0){firstX=x; context.moveTo(x, y);}else{switch (chartOptions.interpolation){case \"linear\": case \"line\":{context.lineTo(x,y); break;}case \"bezier\": default:{context.bezierCurveTo( Math.round((lastX + x) / 2), lastY, Math.round((lastX + x)) / 2, y, x, y); break;}case \"step\":{context.lineTo(x,lastY); context.lineTo(x,y); break;}}}lastX=x; lastY=y;}if (dataSet.length > 1){if (seriesOptions.fillStyle){context.lineTo(dimensions.width + seriesOptions.lineWidth + 1, lastY); context.lineTo(dimensions.width + seriesOptions.lineWidth + 1, dimensions.height + seriesOptions.lineWidth + 1); context.lineTo(firstX, dimensions.height + seriesOptions.lineWidth); context.fillStyle=seriesOptions.fillStyle; context.fill();}if (seriesOptions.strokeStyle && seriesOptions.strokeStyle !=='none'){context.stroke();}context.closePath();}context.restore();}if (chartOptions.tooltip && this.mouseX >=0){context.lineWidth=chartOptions.tooltipLine.lineWidth; context.strokeStyle=chartOptions.tooltipLine.strokeStyle; context.beginPath(); context.moveTo(this.mouseX, 0); context.lineTo(this.mouseX, dimensions.height); context.closePath(); context.stroke(); this.updateTooltip();}if (!chartOptions.labels.disabled && !isNaN(this.valueRange.min) && !isNaN(this.valueRange.max)){var maxValueString=chartOptions.yMaxFormatter(this.valueRange.max, chartOptions.labels.precision), minValueString=chartOptions.yMinFormatter(this.valueRange.min, chartOptions.labels.precision), maxLabelPos=chartOptions.scrollBackwards ? 0 : dimensions.width - context.measureText(maxValueString).width - 2, minLabelPos=chartOptions.scrollBackwards ? 0 : dimensions.width - context.measureText(minValueString).width - 2; context.fillStyle=chartOptions.labels.fillStyle; context.fillText(maxValueString, maxLabelPos, chartOptions.labels.fontSize); context.fillText(minValueString, minLabelPos, dimensions.height - 2);}if ( chartOptions.labels.showIntermediateLabels && !isNaN(this.valueRange.min) && !isNaN(this.valueRange.max) && chartOptions.grid.verticalSections > 0){var step=(this.valueRange.max - this.valueRange.min) / chartOptions.grid.verticalSections; var stepPixels=dimensions.height / chartOptions.grid.verticalSections; for (var v=1; v < chartOptions.grid.verticalSections; v++){var gy=dimensions.height - Math.round(v * stepPixels); if (chartOptions.grid.sharpLines){gy -=0.5;}var yValue=chartOptions.yIntermediateFormatter(this.valueRange.min + (v * step), chartOptions.labels.precision); intermediateLabelPos=chartOptions.labels.intermediateLabelSameAxis ? (chartOptions.scrollBackwards ? 0 : dimensions.width - context.measureText(yValue).width - 2) : (chartOptions.scrollBackwards ? dimensions.width - context.measureText(yValue).width - 2 : 0); context.fillText(yValue, intermediateLabelPos, gy - chartOptions.grid.lineWidth);}}if (chartOptions.timestampFormatter && chartOptions.grid.millisPerLine > 0){var textUntilX=chartOptions.scrollBackwards ? context.measureText(minValueString).width : dimensions.width - context.measureText(minValueString).width + 4; for (var t=time - (time % chartOptions.grid.millisPerLine); t >=oldestValidTime; t -=chartOptions.grid.millisPerLine){var gx=timeToXPixel(t); if ((!chartOptions.scrollBackwards && gx < textUntilX) || (chartOptions.scrollBackwards && gx > textUntilX)){var tx=new Date(t), ts=chartOptions.timestampFormatter(tx), tsWidth=context.measureText(ts).width; textUntilX=chartOptions.scrollBackwards ? gx + tsWidth + 2 : gx - tsWidth - 2; context.fillStyle=chartOptions.labels.fillStyle; if(chartOptions.scrollBackwards){context.fillText(ts, gx, dimensions.height - 2);}else{context.fillText(ts, gx - tsWidth, dimensions.height - 2);}}}}context.restore();}; SmoothieChart.timeFormatter=function(date){function pad2(number){return (number < 10 ? '0' : '') + number}return pad2(date.getHours()) + ':' + pad2(date.getMinutes()) + ':' + pad2(date.getSeconds());}; exports.TimeSeries=TimeSeries; exports.SmoothieChart=SmoothieChart;})(typeof exports==='undefined' ? this : exports);var returned_boost;function getBoost(callback){var xhr=new XMLHttpRequest();xhr.open('GET', '/val');xhr.onload=function(){if (xhr.status===200){returned_boost=xhr.responseText;callback.apply(this,[returned_boost]);}else{return('Request failed. Returned status of ' + xhr.status);}};xhr.send();}var chart=new SmoothieChart({maxValueScale:0.8,grid:{fillStyle:'121212',verticalSections:6},tooltip:true,minValue:0,maxValue:100,horizontalLines:[{color:'#ffffff',lineWidth:1,value:0},{color:'#880000',lineWidth:2,value:80}]}), canvas=document.getElementById('smoothie-chart'), series=new TimeSeries();chart.addTimeSeries(series,{lineWidth:2,strokeStyle:'#ff0000'});chart.streamTo(canvas, 500);setInterval(function(){getBoost();series.append(new Date().getTime(),returned_boost);}, 100);chart.addTimeSeries(series);</script></body></html>");
  });
  //tried getting data from another page, but caused memory issues
  server.on("/val", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", Soilpsi);
  });
  server.begin();
}

void loop() {
  //I guess this lib XOR's everything because it doesn't seem to flicker with this horribly straightforward code
  //turbo logo
  //get boost value
  int oilpsi = getOilPSI(); 
  if (oilpsi > peakPSI){
    peakPSI = oilpsi;
  }
  String SpeakPSI = String(peakPSI);
  Soilpsi = String(oilpsi);
    display.drawString(120, 4, Soilpsi);
    display.drawString(125, 24, "oil");
    display.setFont(ArialMT_Plain_10);
    display.drawString(120, 44, "psi");
  //display peak
  display.setFont(ArialMT_Plain_10);
  display.drawString(128,53,"max " + SpeakPSI);
  display.setFont(ArialMT_Plain_24);
  
  
  //select the right xbm for the number
  if ((oilpsi < 15) && (isInverted == false)) {
    display.invertDisplay();
    isInverted = true;
  }
  if ((oilpsi >= 15) && (isInverted == true)) {
    display.normalDisplay();
    isInverted = false;
  }
  int mappingnumber = map(oilpsi, 0, 100, 0, 22);
  switch (mappingnumber) {
    case 0:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge0_bits);
      break;
    case 1:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge1_bits);
      break;
    case 2:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge2_bits);
      break;
    case 3:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge3_bits);
      break;
    case 4:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge4_bits);
      break;
    case 5:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge5_bits);
      break;
    case 6:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge6_bits);
      break;
    case 7:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge7_bits);
      break;
    case 8:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge8_bits);
      break;
    case 9:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge9_bits);
      break;
    case 10:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge10_bits);
      break;
    case 11:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge11_bits);
      break;
    case 12:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge12_bits);
      break;
    case 13:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge13_bits);
      break;
    case 14:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge14_bits);
      break;
    case 15:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge15_bits);
      break;
    case 16:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge16_bits);
      break;
    case 17:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge17_bits);
      break;
    case 18:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge18_bits);
      break;
    case 19:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge19_bits);
      break;
    case 20:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge20_bits);
      break;
    default:
      display.drawXbm(0, 0, gauge0_width, gauge0_height, gauge20_bits);
  }
  display.display();
  delay(20);
  display.clear();
}

int getOilPSI() {
  float psival = analogRead(36);
  psival = -0.0601*psival + 177.04 - 14.5;
  return psival;
}

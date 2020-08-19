const char index_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>ARDUINO JSON</title>
<script>
function json_process() {
 nocache = "&nocache=" + Math.random() * 1000;
 var request = new XMLHttpRequest();
 request.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
       //console.log("counter");
       var text = this.responseText;
       var obj = JSON.parse(text); 
       var last_adc;
       if (this.responseText != null) {
           document.getElementById("adc_value").innerHTML = obj.adc;   
       }
       last_adc = obj.adc;
       console.log(last_adc);
   }
 }
request.open("GET", "request" + nocache, true);
request.send(null);

setTimeout('json_process()', 1000);
}
</script>
</head>
<body onload="json_process()">
<h1>Arduino AJAX JSON</h1>
<h1 id="adc_value">...</h1>
                        
</body>
</html>
)rawliteral";

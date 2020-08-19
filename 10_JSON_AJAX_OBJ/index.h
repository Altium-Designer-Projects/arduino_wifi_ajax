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
    if(this.readyState == 4 && this.status == 200) {
       //console.log("counter");
       var text = this.responseText;
       var obj = JSON.parse(text); 
       if (this.responseText != null) {
       
           document.getElementById("idName").innerHTML = obj.name;   
           document.getElementById("idYear").innerHTML = obj.year;
           document.getElementById("idCity").innerHTML = obj.city;    
       
       }
   }
 }
request.open("GET", "request" + nocache, true);
request.send(null);
//setTimeout('json_process()', 5000);
}
</script>
</head>
<body onload="json_process()">
<h1>Arduino AJAX JSON</h1><br>
<h2 id="idName">...</h2><br>
<h2 id="idYear">...</h2><br>
<h2 id="idCity">...</h2><br>
</body>
</html>
)rawliteral";

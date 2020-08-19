const char index_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<style>
@import url(https://fonts.googleapis.com/css?family=Montserrat);
@import url(https://fonts.googleapis.com/css?family=Advent+Pro:400,200);
.card{
  font-family:Montserrat,Arial,sans-serif;
  max-width: 600px;
  min-height: 250px;
  background: #82E0AA;
  padding: 30px;
  box-sizing: border-box;
  color: #515A5A;
  margin:100px auto;
  position: relative;
  box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);}
}
</style>
<body>

<div class="card">

 <h1>www.altiumdesignerprojects.com</h1><br><br><br>
 <h1>W1500 & SI7021 AJAX EXAMPLE</h1><br>
 <h1>Temperature : <span id="temp_rsp">...</span></h1>
 <h1>Humidity : <span id="hum_rsp">...</span></h1>

</div>

<script>

setInterval(function() { ajax_func(); }, 1000); 

function ajax_func(){
  nocache = "&nocache=" + Math.random() * 1000;  
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
       document.getElementById("temp_rsp").innerHTML = this.responseXML.getElementsByTagName("temp")[0].childNodes[0].nodeValue;
       document.getElementById("hum_rsp").innerHTML = this.responseXML.getElementsByTagName("hum")[0].childNodes[0].nodeValue;
    }
  };
  xhttp.open("GET", "request" + nocache, true);
  xhttp.send();
}
</script>
</body>
</html>
)rawliteral";

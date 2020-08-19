const char index_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<style>
@import url(https://fonts.googleapis.com/css?family=Montserrat);
@import url(https://fonts.googleapis.com/css?family=Advent+Pro:400,200);
.card{
  font-family:Montserrat,Arial,sans-serif;
  max-width: 400px;
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
  <h1>Sensor Value:<span id="ADCValue">...</span></h1><br>
</div>
<script>

setInterval(function() { read_adc(); }, 500); 

function read_adc() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "request", true);
  xhttp.send();
}
</script>
</body>
</html>
)rawliteral";

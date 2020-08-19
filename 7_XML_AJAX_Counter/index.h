const char index_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>

<style>
#demo{
  width:400px;
  margin:0 auto;
  margin-top:130px;
  font-size:150px;
  color : rgb(0, 64, 255);
}
</style>

<body onload = "counter()">

<div id = "demo">...</div>
 <script>
  function counter(){
    nocache = "&nocache=" + Math.random() * 1000;
    var request = new XMLHttpRequest();
    request.onreadystatechange = function(){
      if(this.readyState == 4 && this.status == 200) {
         console.log("counter");
        
         if(this.responseXML != null){
            document.getElementById("demo").innerHTML = this.responseXML.getElementsByTagName("counter")[0].childNodes[0].nodeValue;
         }
         
      }
    }
    request.open("GET", "request" + nocache, true);
    request.send(null);
    setTimeout('counter()', 1000);
  }
 </script>
</body>
</html>)=====";

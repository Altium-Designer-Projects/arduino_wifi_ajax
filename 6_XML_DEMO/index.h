const char index_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>

<body onload = "ajax_process()">

<h1 id = "name">...</h1><br>
<h1 id = "city">...</h1><br>

 <script>
  function ajax_process(){
    nocache = "&nocache=" + Math.random() * 1000;
    var request = new XMLHttpRequest();
    request.onreadystatechange = function(){
      if(this.readyState == 4 && this.status == 200) {
         
        document.getElementById("name").innerHTML = this.responseXML.getElementsByTagName("name")[0].childNodes[0].nodeValue;
        document.getElementById("city").innerHTML = this.responseXML.getElementsByTagName("city")[0].childNodes[0].nodeValue;
              
      }
    }
    request.open("GET", "request" + nocache, true);
    request.send(null);
    //setTimeout('ajax_process()', 1000);
  }
 </script>
</body>
</html>)=====";

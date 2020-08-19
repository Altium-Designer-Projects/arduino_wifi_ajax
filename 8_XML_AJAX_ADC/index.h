const char index_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <title>Ajax with XML</title>

    </head>
    <body onload="adc_reading()">
        <h1>Web Page using Ajax with XML</h1>
        <h1>Analog : </h1><h1 id="input_adc">...</h1>
        <script>
        function adc_reading()
        {
            nocache = "&nocache=" + Math.random() * 1000;
            var request = new XMLHttpRequest();
            request.onreadystatechange = function()
            {
                if (this.readyState == 4) {
                    if (this.status == 200) {
                        if (this.responseXML != null) {
                            document.getElementById("input_adc").innerHTML = this.responseXML.getElementsByTagName("analog")[0].childNodes[0].nodeValue;
                        }
                    }
                }
            }
            request.open("GET", "request" + nocache, true);
            request.send(null);
            setTimeout('adc_reading()', 1000);
        }
    </script>        
    </body>
</html>)=====";

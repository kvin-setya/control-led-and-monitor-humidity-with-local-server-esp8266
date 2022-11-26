static const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <title>Praktikum WEB SERVER ESP8266</title>
    <style>
      body {
        font-family: Verdana, Geneva, Tahoma, sans-serif;
      }
      .switch {
        position: relative;
        display: inline-block;
        width: 60px;
        height: 34px;
      }

      .switch input {
        opacity: 0;
        width: 0;
        height: 0;
      }

      .slider {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        -webkit-transition: 0.4s;
        transition: 0.4s;
      }

      .slider:before {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        left: 4px;
        bottom: 4px;
        background-color: white;
        -webkit-transition: 0.4s;
        transition: 0.4s;
      }

      input:checked + .slider {
        background-color: #2196f3;
      }

      input:focus + .slider {
        box-shadow: 0 0 1px #2196f3;
      }

      input:checked + .slider:before {
        -webkit-transform: translateX(26px);
        -ms-transform: translateX(26px);
        transform: translateX(26px);
      }

      /* Rounded sliders */
      .slider.round {
        border-radius: 34px;
      }

      .slider.round:before {
        border-radius: 50%;
      }
      .flex-container {
        display: flex;
        background-color: DodgerBlue;
        margin: auto;
        width: 98%;
        padding: 10px;
      }

      .flex-container > div {
        background-color: #f1f1f1;
        margin: 10px;
        padding: 20px;
        font-size: 30px;
      }
      .card {
        box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2);
        transition: 0.3s;
        margin: auto;
        width: 40%;
        padding: 10px;
      }

      .card:hover {
        box-shadow: 0 8px 16px 0 rgba(0, 0, 0, 0.2);
      }

      .container {
        padding: 2px 16px;
      }
      .button {
        background-color: #4caf50; /* Green */
        border: none;
        color: white;
        padding: 16px 32px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 4px 2px;
        transition-duration: 0.4s;
        cursor: pointer;
      }
      .button3 {
        background-color: white;
        color: black;
        border: 2px solid #f44336;
      }

      .button3:hover {
        background-color: #f44336;
        color: white;
      }
    </style>
  </head>
  <body>
    <header></header>
    <main>
      <div>
        <center>
          <h1>WIFI LED CONTROL USING WEMOS D1</h1>
          <br />
          <div>Status LED : <span id="status">NULL</span></div>
          <br />
          <div class="flex-container">
            <div class="card">
              <h1>TEMPERATURE</h1>
              <hr />
              <div class="container">
                <h2><span id="temperature">50</span>'c</h2>
                <p> </p>
              </div>
            </div>
            <div class="card">
              <h1>HUMIDITY</h1>
              <hr />
              <div class="container">
                <h2 id="humidity">50%</h2>
                <p> </p>
              </div>
            </div>
            <div class="card">
              <p>LED SWITCH</p>
              <label class="switch">
                <input type="checkbox" id="led" onchange="ledButton('led')" />
                <span class="slider round"></span>
              </label>
              <p>LED BLINK</p>
              <button class="button button3" onclick="blink()">BLINK LED</button>
              <br />
            </div>
          </div>
          <hr />
          <a href="https://indobot.co.id">Indobot Academy</a>
        </center>
      </div>
    </main>
    <footer></footer>
  </body>
  <script>
    
    setInterval(function () {
      temp();
      hum();
    }, 1500);

    function temp() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("temperature").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/temp", true);
      xhttp.send();
    }

    function hum() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("humidity").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/hum", true);
      xhttp.send();
    }
    

    function ledButton(id) {
      const button = document.getElementById(id);
      if (button.checked) {
        var url = "/ledOn";
      } else {
        var url = "/ledOff";
      }
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("status").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", url, true);
      xhttp.send();
    }

    function blink() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("status").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/ledBlink", true);
      xhttp.send();
    }
  </script>
</html>


)=====";
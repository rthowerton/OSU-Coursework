var req = new XMLHttpRequest();
req.open("GET", "https://na.api.pvp.net/api/lol/na/v1.4/summoner/by-name/abogus1?api_key=RGAPI-0e68264c-6f5d-448d-9f0c-5166980d00e4", true);
//req.setRequestHeader("Content-Type", "text/plain");
//req.setRequestHeader("Content-Type", "application/json");
req.addEventListener("load", function(){
   if(req.status >= 200 && req.status < 400){
      var result = JSON.parse(req.responseText);
      document.getElementById("result").textContent = result;
   }
   else
      console.log("Error in Request: " + req.statusText);
});
req.send();

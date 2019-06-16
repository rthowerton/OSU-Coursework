//upon loading document, call bindButtons
document.addEventListener("DOMContentLoaded", bindButtons);

//gives each submit button an event
function bindButtons(){
   document.getElementById("zipSubmit").addEventListener("click", submit);
   document.getElementById("citySubmit").addEventListener("click", submit);
   document.getElementById("postSubmit").addEventListener("click", subPost);
}

/* instead of making two functions, I made a single function that depends on the user only entering a request into one field at a time. The function checks for which field is full, and gives the text content to whichever URL can accept that type of information.
 */
function submit(event){
   var req = new XMLHttpRequest();
   var input = {content: null};
   var a = document.getElementById("zipCode").value;
   var b = document.getElementById("cityState").value;
   
   //check for filled text input
   if(a != null && a != ""){
      input.content = a;
      req.open("GET","http://api.openweathermap.org/data/2.5/weather?zip=" + input.content + "&appid=fa7d80c48643dfadde2cced1b1be6ca1", true);
   }
   else if(b != null && b != ""){
      input.content = b;
      req.open("GET","http://api.openweathermap.org/data/2.5/weather?q=" + input.content + "&appid=fa7d80c48643dfadde2cced1b1be6ca1", true);
   }
   
   //asynchronous call with error handling
   req.addEventListener("load", function(){
      if(req.status >= 200 && req.status < 400){
         var result = JSON.parse(req.responseText);
         document.getElementById("city").textContent = "City: " + result.name;
         document.getElementById("temp").textContent = "Temperature: " + result.main.temp;
         document.getElementById("humid").textContent = "Humidity: " + result.main.humidity;
      }
      else
      console.log("Error in request: " + req.statusText);
   });
   req.send(JSON.stringify(input));
   
   event.preventDefault();
}

//separate function for submission by POST
function subPost(event){
   var postReq = new XMLHttpRequest();
   var text = {data: null};
   text.data = document.getElementById("subPost").value;
   postReq.open("POST", "http://httpbin.org/post", true);
   postReq.setRequestHeader("Content-Type", "application/json");

   //asynchronous call with error handling
   postReq.addEventListener("load", function(){
      if(postReq.status >= 200 && postReq.status < 400){
	 var response = JSON.parse(postReq.responseText);
	 document.getElementById("display").textContent = response.data;
      }
      else
	 console.log("Error in request: " + response.statusText);
   });

   postReq.send(JSON.stringify(text));
   event.preventDefault();
}

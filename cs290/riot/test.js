var url = "https://na.api.pvp.net";
var api = "/api/lol/na/v1.4/summoner/by-name/abogus1?";
var api_key = "RGAPI-0e68264c-6f5d-448d-9f0c-5166980d00e4";
var express = require("express");
var request = require("request");

var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.set("port", 3436);

app.get("/", function(req, res){
   res.render("front");
});

app.get("/riot", function(req, res, next){
   var context = {};
   request(url+api+api_key, function(err, response, body){
      if(!err && response.statusCode < 400){
	 context.owm = body;
	 res.render("test", context);
      }
      else{
	 if(response){
	    console.log(response.statusCode);
	 }
	 next(err);
      }
   });
});

/*https.get(url+api+api_key, function(res){
   console.log("status code = " + res.statusCode);
   console.log("content type = " + res.headers["content-type"]);
   console.log("content = " + JSON.parse(res.responseText));
});*/

/*app.get("/test", function(req, res){
   var callTo = url+api+api_key;
   var request = https.get(callTo, function(call, response){
      return response
   });
   for(param in request){
      console.log("Parameter name: " + param);
   }

   var result = {};
   result.name = request.name;
   
   res.render("test", result);
});*/

app.use(function(req, res){
   res.status(404);
   res.render("404");
});

app.use(function(err, req, res, next){
   console.error(err.stack);
   res.type("plain/text");
   res.status(500);
   res.render("500");
});

app.listen(app.get("port"), function(){
   console.log("App started on http://flip3.engr.oregonstate.edu:" + app.get("port") + "; press Ctrl-C to terminate.");
});






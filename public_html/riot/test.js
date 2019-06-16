var url = "https://na.api.pvp.net";
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
   var api = "/api/lol/na/v1.4/summoner/by-name/bjergsen?api_key=";
   var context = {};
   request(url+api+api_key, function(err, response, body){
      if(!err && response.statusCode < 400){
	 var array = JSON.parse(body);
	 for(var param in array.bjergsen){
	    context[param] = array.bjergsen[param].toString();
	    console.log(param + ": " + context[param]);
	 }
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

app.listen(app.get("port"), function(){
   console.log("App started on http://flip3.engr.oregonstate.edu:" + app.get("port") + "; press Ctrl-C to terminate.");
});

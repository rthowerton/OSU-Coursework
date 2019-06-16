/*
 * The following code was borrowed from the weekly lectures.
 */
var express = require("express");

var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});
var bodyParser = require("body-parser");

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.set("port", 1997);

/*
 * End copy.
 */

app.get("/", function(req, res){
   res.render("home");
});

/*
 * For the following two the lectures were only used as a reference for keywords and syntax.
 */

app.get("/show-request", function(req, res){
   var response = {};//"object" to contain response info
   response.type = "GET";//type of request
   var data = [];//array to store key-value pairs
   for(var key in req.query){
      data.push({"key":key, "value":req.query[key]});//add user data to array
   }

   response.content = data;//set response content to the data list
   res.render("show-request", response);//render show-request with filled response
});

app.post("/show-request", function(req, res){
   var response = {};//variable to contain response info
   response.type = "POST";//type of request
   var data = [];//array to store key-value pairs
   var cont = [];//array to store content from body
   
   for(var key in req.query){
      data.push({"key":key, "value":req.query[key]});//add query data to array
   }

   response.body = "Body Content";//read content from POST body
   for(var key in req.body){
      cont.push({"key":key, "value":req.body[key]});//add user data to array
   }

   response.content = data;//set response content to the data list
   response.post = cont;//set response post to the cont list
   res.render("show-request", response);//render show-request with filled response
});

/*
 * Lecture code for errors and page launch.
 */

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
   console.log("Express started on htpp://flip3.engr.oregonstate.edu:" + app.get("port") + "; press Ctrl-C to terminate.");
});

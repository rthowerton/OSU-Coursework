var express = require("express");

var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});
var session = require("express-session");
var bodyParser = require("body-parser");

app.use(bodyParser.urlencoded({extnded: false}));
app.use(session({secret:"p@55word"}));

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.set("port", 3436);

app.get("/counter", function(req, res){
   var context = {};
   context.count = req.session.count || 0;
   req.session.count = context.count + 1;
   res.render("counter", context);
});

app.post("/counter", function(req, res){
   var context = {};
   if(req.body.command === "resetCount"){
      req.session.count = 0;
   }
   else{
      context.err = true;
   }

   context.count = req.session.count || 0;
   req.session.count = context.count + 1;
   res.render("counter", context);
});

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
   console.log("App started on port " + app.get("port") + "; press Ctrl-C to terminate.");
});

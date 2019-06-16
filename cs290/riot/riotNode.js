var riot = require("riot-games-api-nodejs");
var express = require("express");

var app = express();
app.set("port", 3436);

app.get("/", function(req, res){
   res.render("front");
});

app.get("/test", function(req, res){
   var result = riot.summoner.byName("abogus1", {});
   res.render("test", result.name);
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

app.listen(app.get("port"));

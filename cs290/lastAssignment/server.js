var express = require("express");

var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});
var mysql = require("./dbcon.js");

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.set("port", 3436);

//get full table and send it to the tracker
app.get("/", function(req, res){
   mysql.pool.query("SELECT * FROM exercises", function(err, rows, fields){
      if(err){
	 next(err);
	 return;
      }
      res.type("application/json");
      res.set("Access-Control-Allow-Origin", "*");
      res.send(JSON.stringify(rows));
   });
});

//insert new exercise into table
app.get("/insert", function(req, res, next){
   mysql.pool.query("INSERT INTO exercises (`name`,`reps`,`weight`,`date`,`lbs`) VALUES (?,?,?,?,?)", [req.query.name, req.query.reps, req.query.weight, req.query.date, req.query.lbs], function(err, result){
      if(err){
	 next(err);
	 return;
      }
      res.type("text/plain");
      res.set("Access-Control-Allow-Origin", "*");
      res.send();
   });
});

//update exercise currently in the table
//(uses the safe update from the lectures)
app.get("/update", function(req, res, next){
   var context = {};
   mysql.pool.query("SELECT * FROM exercises WHERE id=?", [req.query.id], function(err, result){
      if(err){
	 next(err);
	 return;
      }
      if(result.length == 1){
	 var curVals = result[0];
	 mysql.pool.query("UPDATE exercises SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id=?",
	    [req.query.name || curVals.name, req.query.reps || curVals.reps, req.query.weight || curVals.weight, req.query.date || curVals.date, req.query.lbs || curVals.lbs, req.query.id],
	    function(err, result){
	       if(err){
                  next(err);
		  return;
	       }
	       res.type("text/plain");
	       res.set("Access-Control-Allow-Origin", "*");
	       res.send();
	    });
      }
   });
});

//delete specified row from the table
app.get("/delete", function(req, res, next){
   mysql.pool.query("DELETE FROM exercises WHERE id=(?)", [req.query.id], function(err, result){
      if(err){
	 next(err);
	 return;
      }
      res.type("text/plain");
      res.set("Access-Control-Allow-Origin", "*");
      res.send();
   });
});

//provided reset-table function
app.get("/reset-table", function(req, res, next){
   var context = {};
   mysql.pool.query("DROP TABLE IF EXISTS exercises", function(err){
      var createString = "CREATE TABLE exercises(" + 
      "id INT PRIMARY KEY AUTO_INCREMENT," + 
      "name VARCHAR(255) NOT NULL," + 
      "reps INT," + 
      "weight INT," + 
      "date DATE," + 
      "lbs BOOLEAN)";
      mysql.pool.query(createString, function(err){
	 context.results = "Table reset";
	 res.render("home", context);
      });
   });
});

app.use(function(req, res){
   res.type("text/plain");
   res.status(404);
   res.send("404 - Not Found");
});

app.use(function(err, req, res, next){
   console.error(err.stack);
   res.type("plain/text");
   res.status(500);
   res.send("500 - Server Error");
});

app.listen(app.get("port"), function (){
   console.log("App started on flip3.engr.oregonstate.edu:" + app.get("port") + "; press Ctrl-C to terminate.");
});

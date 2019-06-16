var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'mysql.eecs.oregonstate.edu',
  user            : 'cs290_howertor',
  password        : '3436',
  database        : 'cs290_howertor'
});

module.exports.pool = pool;

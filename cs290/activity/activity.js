testList();
function buildList(list){
   var result = [];
   for(var i = 0; i < list.length; i++){
      var item = "item" + list[i];
      result.push(function(list, item, x){
	 return function(){
	    console.log(item + ' ' + list[x]);
	 };
      });
   }
   return result;
}

function testList(){
   var fnlist = buildList([1,2,3]);
   for(var j = 0; j < fnlist.length; j++){
      console.log(j);
      fnlist[j]();
   }
}

function deepEqual(obj1, obj2){
   if(obj1 === obj2){//if obviously equivalent
      return true;
   }
   //if both args are non-null objects
   else if(typeof(obj1) == typeof(obj2) && typeof(obj1) == "object" && obj1 != null){
      for(var i in obj1){
	 if(obj1[i] === obj2[i])//if props are equivalent
	    continue;
	 //if props are both objects, recursively call deepEqual on objects
	 else if(typeof(obj1[i]) == "object" && typeof(obj1[i]) == typeof(obj2[i]))
	    return deepEqual(obj1[i], obj2[i]);
	 else if(obj1[i] !== obj2[i])//if props are found to be unequivalent
	    return false;
      }
      return true;//no issues
   }
   else//catch-all
      return false;
}

var obj = {here: {is: "an"}, object: 2};
console.log(deepEqual(obj, obj));//true
console.log(deepEqual(obj, {here: 1, object: 2}));//false
console.log(deepEqual(obj, {here: {is: "an"}, object: 2}));//true

function Map(){this.elements=[];this.size=function(){return this.elements.length};this.isEmpty=function(){return 1>this.elements.length};this.clear=function(){this.elements=[]};this.put=function(a,b){this.elements.push({key:a,value:b})};this.remove=function(a){try{for(i=0;i<this.elements.length;i++)if(this.elements[i].key==a){var b=this.elements[i];this.elements.splice(i,1);return b.value}}catch(c){}return null};this.removebyindex=function(a){try{var b=this.elements[a];this.elements.splice(i,1);return b.value}catch(c){return null}};
this.get=function(a){try{for(i=0;i<this.elements.length;i++)if(this.elements[i].key==a)return this.elements[i].value}catch(b){return null}};this.element=function(a){return 0>a||a>=this.elements.length?null:this.elements[a]};this.containsKey=function(a){var b=!1;try{for(i=0;i<this.elements.length;i++)this.elements[i].key==a&&(b=!0)}catch(c){b=!1}return b};this.containsValue=function(a){var b=!1;try{for(i=0;i<this.elements.length;i++)this.elements[i].value==a&&(b=!0)}catch(c){b=!1}return b};this.values=
function(){var a=[];for(i=0;i<this.elements.length;i++)a.push(this.elements[i].value);return a};this.keys=function(){var a=[];for(i=0;i<this.elements.length;i++)a.push(this.elements[i].key);return a}};
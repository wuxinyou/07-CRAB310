function Map(){this.elements=new Array();this.size=function(){return this.elements.length};this.isEmpty=function(){return(this.elements.length<1)};this.clear=function(){this.elements=new Array()};this.put=function(b,a){this.elements.push({key:b,value:a})};this.remove=function(b){try{for(i=0;i<this.elements.length;i++){if(this.elements[i].key==b){var a=this.elements[i];this.elements.splice(i,1);return a.value}}}catch(c){return null}return null};this.removebyindex=function(c){try{var a=this.elements[c];this.elements.splice(i,1);return a.value}catch(b){return null}return null};this.get=function(a){try{for(i=0;i<this.elements.length;i++){if(this.elements[i].key==a){return this.elements[i].value}}}catch(b){return null}};this.getKey=function(a){try{for(i=0;i<this.elements.length;i++){if(this.elements[i].value==a){return this.elements[i].key}}}catch(b){return null}};this.element=function(a){if(a<0||a>=this.elements.length){return null}return this.elements[a]};this.containsKey=function(a){var c=false;try{for(i=0;i<this.elements.length;i++){if(this.elements[i].key==a){c=true}}}catch(b){c=false}return c};this.containsValue=function(a){var c=false;try{for(i=0;i<this.elements.length;i++){if(this.elements[i].value==a){c=true}}}catch(b){c=false}return c};this.values=function(){var a=new Array();for(i=0;i<this.elements.length;i++){a.push(this.elements[i].value)}return a};this.keys=function(){var a=new Array();for(i=0;i<this.elements.length;i++){a.push(this.elements[i].key)}return a}};
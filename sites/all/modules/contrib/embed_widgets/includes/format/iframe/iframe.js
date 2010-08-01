// $Id: iframe.js,v 1.7.2.3 2009/09/09 03:08:02 jtsnow Exp $

// Test for minimal Javascript required.
if (document.getElementsByTagName && document.createElement && document.createTextNode && document.documentElement && document.getElementById) {
	var DrupalEmbed = DrupalEmbed || [];
	DrupalEmbed[DrupalEmbed.length] = {
	  src: widgetContext['url'],
	  wid: widgetContext['wid'],
	  width: widgetContext['width'],
	  height: widgetContext['height'],
	  jquery: widgetContext['jquery'],
	  new_placement: widgetContext['new_placement'],
	  newID: false,
	  base_url: widgetContext['base_url']
	};

	if (typeof embedWidgetInsert == 'undefined') {
	  embedWidgetInsert = function () {
		  
//        jQuery now loads, so we can use it for embed code interface.
//		  $(document).ready(function(){
//              $("").appendTo("body");
//                      return false;
//              });

		  for (var i in DrupalEmbed) {
		    if (!DrupalEmbed[i]['processed']) {
		      DrupalEmbed[i]['processed'] = true;
		      
		      var separator = DrupalEmbed[i].src.indexOf('?') == -1 ? '?' : '&';
		      
		      // Keep track of how many widgets are embedded in this document.
		      if(undefined===window.widget_count){
		        window.widget_count = 0;
		      }
		      else {
		        widget_count++;
		      }
		      
		      // Use unique ID for each widget on the page.
		      var script = document.getElementById('widget-embed-script-' + DrupalEmbed[i].wid);
		      script.setAttribute('id', 'widget-embed-script-' + DrupalEmbed[i].wid + widget_count);
		      
		      // Create iframe element.
		      var div = document.createElement('div');
		      div.setAttribute('id', 'widget-embed-container' + widget_count);
		      var iframe = document.createElement('iframe');
		      iframe.setAttribute('id', 'widget-embed-' + widget_count);
		      iframe.setAttribute('frameBorder', '0');
		      iframe.setAttribute('width', DrupalEmbed[i].width);
		      iframe.setAttribute('height', DrupalEmbed[i].height);
		      //iframe.setAttribute('style', "border:1px solid #D9EAF5;");
		      iframe.setAttribute('scrolling', 'no');
		      
		      if (DrupalEmbed[i].height) {
		        iframe.myHeight = DrupalEmbed[i].height;
		      }
		      if (DrupalEmbed[i].width) {
                iframe.myWidth = DrupalEmbed[i].width;
		      }
		      iframe.setAttribute('src', DrupalEmbed[i].src + separator + 'widgets_mode=' + DrupalEmbed[i].wid);
		      
		      //var embed_link = document.createElement('a');
		      //embed_link.setAttribute('id', 'widget-embed-link' + widget_count);
		      //embed_link.setAttribute('href', 'javascript:');
		      //embed_link.setAttribute('onClick', "return false;");
		      //embed_link.innerHTML = "Embed";
		      //var link_wrapper = document.createElement('div');
		      //var code_wrapper = document.createElement('div');
		      
		      //var input = document.createElement('input');
        //input.setAttribute('type', 'text');
        //input.setAttribute('value', '<script id="widget-embed-script-' + DrupalEmbed[i].wid +'" src="' + DrupalEmbed[i].base_url + '/embed-widgets/embed/' + DrupalEmbed[i].wid + '/iframe.js"></script>');
        //input.setAttribute('style', 'width: 90%;');
        //input.setAttribute('onClick', "javascript:this.focus(); this.select();");
        
        //var desc_wrapper = document.createElement('div');
        //desc_wrapper.setAttribute('style', 'font-size: 10px; line-height: 150%;');
        //desc_wrapper.innerHTML = "Share by pasting this code into your website:";
		      
		      
		      //code_wrapper.innerHTML = "Code goes here.";
	//	      var newID = false;
		      
//		      $(link_wrapper).click(function () {
//		          //$(code_wrapper).slideDown();
//		          if ($(code_wrapper).is(":hidden")) {
//		            $(code_wrapper).show("slow");
//		            
////		            if (DrupalEmbed[i].newID == false) {
////		              DrupalEmbed[i].newID = true;
////		              $.getJSON(DrupalEmbed[i].new_placement,
////	                    function(data){
////	                      //alert(data.new_widget_id);
////		            	  var input = document.createElement('input');
////		            	  input.setAttribute('type', 'text');
////		            	  input.setAttribute('value', '<script id="widget-embed-script-' + data.new_widget_id +'" src="' + DrupalEmbed[i].base_url + '/embed-widgets/embed/' + data.new_widget_id + '/iframe.js"></script>');
////		            	  code_wrapper.appendChild(input);
////		            	  //<script id="widget-embed-script-bG8ueUV1238UHZYek01c65445sb2NhbGhvc3Q-4-4" src="http://localhost/embed-widgets/embed/bG8ueUV1238UHZYek01c65445sb2NhbGhvc3Q-4-4/iframe.js"></script>
////	                  });
//		              
//		            }
//
//		          } else {
//		            $(code_wrapper).slideUp();
//		          }
//		      });
		      
//		      $(code_wrapper).ready(function () {
//		    	    $(code_wrapper).hide();
//		    	});


		      
		      // Set correct iframe height each time content in iframe changes.
		      iframe.onload = function () {
		  	        var iframeDocument = this.contentDocument ? this.contentDocument : (this.contentWindow ? this.contentWindow.document : null);
		  	        
		  	        if (iframeDocument) {
		  	          //$("#container > *", iframeDocument).css({'max-width' : (this.myWidth - 20) + 'px'});
		  	          //var height = iframeDocument.innerHeight || iframeDocument.body.scrollHeight;  // Does not work cross-domain
		  	          //var width = iframeDocument.innerWidth || iframeDocument.body.scrollWidth;
		  	          var height = this.myHeight;
		  	          var width = this.myWidth;
		  	          
//		  	          if (height > parseInt(this.myHeight, 10)) {
//		  	            width += 14;
//		  	          }
		  	          
//		  	          if (this.myHeight) {
//		  	            //iframeDocument.getElementById('container').style.height = this.myHeight + 'px';
//		  	            height = parseInt(this.myHeight, 10) + 15;
//		  	          }		  	          
//		  	          else {
//		  	        	//iframeDocument.getElementById('container').style.height = (height) + 'px';
//		  	        	height = iframeDocument.height || iframeDocument.body.scrollHeight;
//		  	        	this.myHeight = height;
//		  	          }
//		  	          if (!this.myWidth && width) {
//	  	            	this.setAttribute('width', width);
//	  	            	//$('#widget-embed-container' + widget_count).css({'width' : (width) + 'px'});
//	  	           }
		  	          this.setAttribute('height', height);
		  	          this.setAttribute('width', width);
		  	          //$('#widget-embed-container' + widget_count).css({'width' : (width) + 'px', 'display' : 'block'});
		  	          //this.parentNode.setAttribute('height', height);
		  	          
		  	        }
		      };
		      
		      // Insert iframe into document.
		      script.parentNode.insertBefore(iframe, script);
		      //script.parentNode.insertBefore(div, script);
		      //div.appendChild(iframe);
		      //div.appendChild(link_wrapper);
		      //link_wrapper.appendChild(embed_link);
		      //div.appendChild(desc_wrapper);
		      //div.appendChild(code_wrapper);
		      //code_wrapper.appendChild(input);
		      //$(code_wrapper).hide();
		      //code_wrapper.appendChild(form);
		      //code_wrapper.appendChild(input);
		      

		    }
		  }
	  };
	}
	
  if (typeof jQuery == 'undefined') {  
    var headID = document.getElementsByTagName("head")[0];         
    var newScript = document.createElement('script');
    newScript.type = 'text/javascript';
    newScript.onload = embedWidgetInsert;
    newScript.src = DrupalEmbed[0].jquery;
    headID.appendChild(newScript);
  }
  embedWidgetInsert();

}


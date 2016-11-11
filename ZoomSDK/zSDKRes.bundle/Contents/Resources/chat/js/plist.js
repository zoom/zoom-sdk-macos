$(function () {

    var DATA_REPEAT = 6;
    var plistNode = $('ul.plist'),
        hiddenIdSel = 'input[type=hidden][name=id]',
        chatWithAllButton = $('div.withall input');

    
    window.InitUI = function (chatWithAllText) {
        chatWithAllButton.val(chatWithAllText);
    };
  
    // "id", "pic url", "name", "audio", "video", "unread", "id", "pic url", "name", "audio", "video", "unread", ...
    // "101101", "/data/avatar_101001.png", "Sanshi Zhang", "0/1", "0/1/2", "5", ...
    window.UpdatePList = function () {
        var i, count = Math.floor(arguments.length / DATA_REPEAT), html = [], audiourl, videourl, photourl, unread, totalUnread;
        for (i = 0; i < count; i++) {
            photourl = arguments[i * DATA_REPEAT + 1];
            if (!photourl) {
                photourl = './images/people_icon_b.png';
            }

            audiourl = arguments[i * DATA_REPEAT + 3];
            if (audiourl === '0') {
                audiourl = './images/btn_mute.png';
            } else {
                audiourl = './images/btn_unmute.png';
            }

            videourl = arguments[i * DATA_REPEAT + 4];
            if (videourl === '0') {
                videourl = './images/btn_stopvideo.png';
            } else if (videourl === '1') {
                videourl = './images/btn_sendvideo.png';
            } else {
                videourl = './images/btn_empty.png';
            }
			
			

			if(i < count - 1) {
				html.push('<li class="people">');
			} else {
				html.push('<li class="me">');
			}
            html.push('<div class="photo"><img src="' + photourl + '" alt="photo"></div>');
            html.push('<div class="name">' + htmlEncode(arguments[i * DATA_REPEAT + 2]) + '</div>');
			
			unread = parseInt(arguments[i * DATA_REPEAT + 5], 10);
			if(unread > 0) {
				html.push('<div class="unread">'+ unread +'</div>');
			}
			
            html.push('<div class="audio"><img src="' + audiourl + '" alt="audio"></div>');
            html.push('<div class="video"><img src="' + videourl + '" alt="video"></div>');
            html.push('<input type="hidden" name="id" value="' + arguments[i * DATA_REPEAT] + '" />');
            html.push('</li>');
        }
  
        plistNode.html(html.join(''));
  
        totalUnread = parseInt(arguments[arguments.length - 1], 10);
  if(totalUnread == 0){
    chatWithAllButton.val('Chat with All');
  } else {
    chatWithAllButton.val('Chat with All (' + totalUnread + ')');
  }
                             
  
    };

    function htmlEncode(str) {
        str = str + '';
        return str.replace(/&/g, '&amp;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#39;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/ /g, '&nbsp;');
    }


	plistNode.delegate('li.people', 'hover', function() {
		$(this).toggleClass('hover'); 
    });
    
	plistNode.delegate('li.people', 'click', function() {
		var $this = $(this);
		var cocoa = window.CocoaChatWindow;
        	if(cocoa) {
            		cocoa.chatWithPeople($this.find(hiddenIdSel).val());
        	}
	});

	chatWithAllButton.click(function() {
		var cocoa = window.CocoaChatWindow;
        	if(cocoa) {
            		cocoa.chatWithAll();
        	}
	});
});

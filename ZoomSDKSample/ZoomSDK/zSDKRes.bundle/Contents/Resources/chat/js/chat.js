$(function () {

    var arrays = [], chatArea = $('#chats'), chatAreaContainer = $('#chatsContainer'), scrollBarInstance;
    var shortMonths = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
    var longMonths = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
    var shortDays = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
    var longDays = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
	
	var ua = navigator.userAgent;
	var isPad = /iPad/i.test(ua);
    var isiPhone = !isPad && /iPhone/i.test(ua);
	//isPad = true;
	
    var NORMAL_LI_TEMPLATE =
                '<li class="normal">' +
                    '<div class="photo">' +
    //'<a href="javascript:;">' +
                            '<img src="{{senderPicUrl}}" alt="{{senderName}}" />' +
    //'</a>' +
                    '</div>' +
                    '<div class="time">{{timeStr}}</div>' +
                    '<div class="messages">' +
                        '<div class="message">{{{message}}}</div>' +
                    '</div>' +
                '</li>';

    if (INMEETING) {
        NORMAL_LI_TEMPLATE =
                '<li class="normal">' +
                    '<div class="photo">' +
        //'<a href="javascript:;">' +
                            '<img src="{{senderPicUrl}}" alt="{{senderName}}" />' +
        //'</a>' +
                    '</div>' +
                    '<div class="time">{{timeStr}}</div>' +
                    '<div class="name {{#isPrivate}}private{{/isPrivate}}">{{senderName}}</div>' +
                    '<div class="messages">' +
                        '<div class="message">{{{message}}}</div>' +
                    '</div>' +
                '</li>';
    }


    var DATE_LI_TEMPLATE = '<li class="date">{{dateStr}}</li>';

    var AM_PM_TEMPLATE = '{{hours}}:{{minutes}}{{ampm}}';

    var COMMAND_LI_TEMPLATE =
        '<li class="command">' +
			'<div class="messagecontainer">' +
			'<div class="message">{{{message}}}</div>' +
			'</div>' +
			'<div class="time">{{timeStr}}</div>' +
    //'<div class="alert-message info">' +
    //    '<p>{{{message}}}&nbsp;<a href="#">{{cmdText}}</a></p>' +
    //'</div>' +
        '</li>';

    
    window.ClearAll = function () {
        arrays = [];
        chatArea.html('');
    };
  
    window.GetItemCount = function () {
        return arrays.length;
    };
	
	window.UpdateTypingMessage = function (msg) {
		var typingNode = $('#typing');
		if(msg) {
			typingNode.text(msg).show();
		} else {
			typingNode.text('').hide();
		}
	};

    window.AddTextMsgItem = function (id, senderId, senderName, isSelf, senderPicUrl, message, dateStr, isPrivate) {
        var date = new Date(parseInt(dateStr, 10));
        isSelf = checkBool(isSelf);
        isPrivate = checkBool(isPrivate);
        if(!senderPicUrl){
            senderPicUrl = 'images/people_icon_b.png';
        }
        message = htmlEncode(message);
//		if (!isPad) {
			message = replaceLinks(message);
//		}
        message = message.replace(/\r\n/g, '<br/>').replace(/\n/g, '<br/>');
        var data = {
            id: id,
            senderId: senderId,
            senderName: senderName,
            isSelf: isSelf,
            senderPicUrl: senderPicUrl,
            message: message,
            date: date,
            timeStr: time12(date),
			isPrivate: isPrivate
        };

        if (!INMEETING) {
            appendDateLi(date);
        }

        if (isANewItem(data)) {
            $(Mustache.to_html(NORMAL_LI_TEMPLATE, data)).appendTo(chatArea);
        } else {
            chatArea.find('li:last-child .messages').append('<div class="message">' + message + '</div>');
        }

        if(!NATIVESCROLLBAR) {
            initScrollBar();
        }
        scrollToBottom();

        arrays.push(data);
    }

    window.AddCmdItem = function (id, message, dateStr, cmdType, cmdText, cmdParam1, cmdParam2) {
        var date = new Date(parseInt(dateStr, 10));
        var data = {
            id: id,
            message: message,
            date: date,
            timeStr: time12(date),
            cmdType: cmdType,
            cmdText: cmdText,
            cmdParam1: cmdParam1,
            cmdParam2: cmdParam2
        };

        appendDateLi(date);


        $(Mustache.to_html(COMMAND_LI_TEMPLATE, data)).appendTo(chatArea).data('datasource', data);

        if(!NATIVESCROLLBAR) {
            initScrollBar();
        }
        scrollToBottom();
        
        arrays.push(data);
    }

    window.UpdateCmdItem = function (id, message, timeStr, cmdType, cmdText, cmdParam1, cmdParam2) {

    }
  
    function scrollToBottom() {
        if(!NATIVESCROLLBAR) {
            scrollBarInstance.scrollToBottom();
        } else {
            $('html,body').scrollTop(100000);
			//chatAreaContainer.scrollTop(100000);
        }
    }

    function checkBool(param) {
        if(typeof(param) === 'string') {
            return (param === 'true' || param === '1' || param === 'YES') ? true : false;
        }
        return !!param;
    }

    function htmlEncode(str) {
        str = str + '';
        return str.replace(/&/g, '&amp;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#39;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;');
            //.replace(/ /g, '&nbsp;');
    }


    function replaceLinks(message) {
        var pattern = /(http|https|ftp|ftps)\:\/\/\S+/ig;
        var replace = '<a target="_blank" href=\"$&\">$&</a>';
        return message.replace(pattern, replace);
    }


    function isANewItem(data) {
        if (!arrays.length) {
            return true;
        }

        var lastData = arrays[arrays.length - 1];
        if (lastData.senderId !== data.senderId 
            || lastData.isPrivate !== data.isPrivate
            || lastData.senderName !== data.senderName) {
            return true;
        } else {
            if (data.date - lastData.date < 5 * 60 * 1000) {
                return false;
            } else {
                return true;
            }
        }

    }

    function appendDateLi(date) {
        function isANewDay() {
            var lastDate = arrays[arrays.length - 1].date;

            if (date.getFullYear() === lastDate.getFullYear() &&
                date.getDate() === lastDate.getDate() &&
                date.getMonth() === lastDate.getMonth()) {
                return false;
            }
            return true;
        }

        if (!arrays.length || isANewDay()) {
            var dateStr = longMonths[date.getMonth()] + ' ' + date.getDate();
            $(Mustache.to_html(DATE_LI_TEMPLATE, {
                dateStr: dateStr
            })).appendTo(chatArea);
        }
    }


    function time12(date) {
        var ampm = 'am';
        var hours = date.getHours();
        var minutes = date.getMinutes();
        if (minutes < 10) {
            minutes = '0' + minutes;
        }

        if (hours >= 12) {
            ampm = 'pm';
        }

        if (hours > 12) {
            hours -= 12;
        }

        // 12hour		24hour
        // 12:01am		0:01
        // 12:59am		0:59
        // 1:00am		1:00
        if (hours === 0) {
            hours = 12;
        }
        return Mustache.to_html(AM_PM_TEMPLATE, {
            hours: hours,
            minutes: minutes,
            ampm: ampm
        });
    }

    
    
	function initScrollBar() {
		var bottomHeight = 0;
		if(!INMEETING) {
			bottomHeight = 0;
		}
		chatAreaContainer.height($(window).height() - bottomHeight);
		//chatAreaContainer.width($(window).width());
		
		if(!NATIVESCROLLBAR) {	 
			if (!scrollBarInstance) {
				chatAreaContainer.jScrollPane({
					horizontalGutter: 5,
					verticalGutter: 5,
					showArrows: false,
					contentWidth: $(window).width()
				});
				
				scrollBarInstance = chatAreaContainer.data('jsp');
			} else {
				scrollBarInstance.reinitialise({
					contentWidth: $(window).width()
				});
			}	 
		}
		
	}
        
	$(window).resize(function () {
		initScrollBar();
	});
	
	initScrollBar();
    
    
    
    /*
    $(document).bind('contextmenu', function () {
        return false;
    });
    */

    if (isPad || isiPhone) {
		chatArea.addClass('ipad');
	}

    if (!INMEETING) {
		if (!isPad && !isiPhone) {
			chatArea.delegate('li.normal', 'hover', function (event) {
				$(this).find('.time').toggle();
			});
		}

        chatArea.delegate('li.command a', 'click', function (event) {
            if (window.external) {
                var data = $(this).parents('li.command').data('datasource');
                window.external.OnEvent(data.cmdType, data.cmdParam1, data.cmdParam2);
            }

            return false;
        });
    }

});
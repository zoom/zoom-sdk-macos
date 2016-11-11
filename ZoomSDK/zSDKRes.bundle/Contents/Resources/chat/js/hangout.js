$(function () {

    var DATA_REPEAT = 5;
    var MAX_USER_COUNT = 200;
    var currentLoginType = 'facebook';
    var tokenNode = $('ul.token-input-list-facebook'),
        inputNode = tokenNode.find('li:last input[type=text]'),
        listNode = $('ul.userlist'),
        hiddenIdSel = 'input[type=hidden][name=id]',
        hiddenCustomEmailSel = 'input[type=hidden][name=customemail]',
        titleNode = $('#title'),
        meetinginfoNode = $('#meetinginfo'),
        copyButtonNode = $('#copyButton'),
        sendEmailButtonNode = $('#sendEmailButton'),
        lastHoveredUserNode;

    window.SetLoginType = function (loginType) {
        //titleNode.html('SetLoginType:' + loginType);
        currentLoginType = loginType;
    };

    window.GetSelectedUsers = function () {
        // First trigger the keydown event of input box.
        endEdit(inputNode.val());

        var users = [];
        tokenNode.find('li.token-input-token-facebook').each(function () {
            var $this = $(this),
                id = $this.find(hiddenIdSel).val(),
                customemail = $this.find(hiddenCustomEmailSel).length ? "true" : "false";
            users.push(id);
            users.push(customemail);
        });
        return users;
    };


    window.UpdateSelectedUsers = function () {

        inputNode.val('');

        tokenNode.find('li.token-input-token-facebook').remove();

        listNode.find('li.selected').removeClass('selected').removeClass('hovered');

        if(arguments.length > 0) {
            AddSelectedUsers.apply(window, arguments);
        }
    };


    // "id", "name", "iscustomemail", "id", "name", "iscustomemail"
    window.AddSelectedUsers = function () {
        var i, count = arguments.length / 3;
        for(i = 0; i < count; i++) {
            AddSelectedUser(arguments[i * 3], arguments[i * 3 + 1], arguments[i * 3 + 2]);
        }
    };

    window.AddSelectedUser = function (id, name, isCustomEmail) {
        var html = [],
            isCustomEmail = checkBool(isCustomEmail),
            liNode;
        html.push('<li class="token-input-token-facebook">');
        html.push('<p>' + name + '</p>');
        html.push('<span class="token-input-delete-token-facebook">&times</span>');
        html.push('<input type="hidden" name="id" value="' + id + '" />');
        if(isCustomEmail) {
            html.push('<input type="hidden" name="customemail" value="' + isCustomEmail + '" />');
        }
        html.push('</li>');
        tokenNode.find('li:last').before(html.join(''));

        if(!isCustomEmail) {
            liNode = findLiNodeByID(id, false);
            if(liNode && !liNode.hasClass('selected')) {
                liNode.removeClass('hovered');
                liNode.addClass('selected');
            }
        }

        resetListNodeHeight();
        tokenNode.scrollTop(100000);

        if(typeof (CocoaHangoutWindow) !== 'undefined') {
            CocoaHangoutWindow.updateHangoutButton();
        }
    };




    window.RemoveSelectedUser = function (idorli, alsoCheckListStatus) {

        var id, li, customemail, alsoCheckListStatus = checkBool(alsoCheckListStatus);
        if(typeof (idorli) === 'string') {
            id = idorli;
            li = findLiNodeByID(id, true);
        } else {
            li = idorli;
            id = li.find(hiddenIdSel).val();
        }
        if(!id || !id.length) {
            return;
        }

        li.remove();

        if(alsoCheckListStatus) {
            customemail = li.find(hiddenCustomEmailSel);
            if(!customemail.length) {
                listNode.find('li.selected').each(function () {
                    var $this = $(this);
                    if($this.find(hiddenIdSel).val() === id) {
                        $this.removeClass('selected');
                        return false;
                    }
                });
            }
        }

        resetListNodeHeight();

        if(typeof (CocoaHangoutWindow) !== 'undefined') {
            CocoaHangoutWindow.updateHangoutButton();
        }

    };

    // "id", "name", "pic url", "online", "custom presence", "id", "name", "pic url", "online", "custom presence" ...
    window.UpdateUserList = function () {
        var i, count = arguments.length / DATA_REPEAT,
            html = [],
            online, onlinetext, onlinecss, onlineimagename, photourl, customPresence;



        var displayUserCount = 0;
        for(i = 0; i < count; i++) {
            online = arguments[i * DATA_REPEAT + 3];
            customPresence = parseInt(arguments[i * DATA_REPEAT + 4], 10);
            online = checkBool(online);
            onlinetext = online ? 'online' : 'offline';
            onlinecss = online ? '' : 'disabled';


			
            onlinecss = '';
            if(displayUserCount > MAX_USER_COUNT) {
            onlinecss += ' hidden';
            } else {
            displayUserCount++;
            }
            // offline - 0, phone - 1, dnd - 2, online - 3;
            onlineimagename = 'available_invite_by_IM';
            if(customPresence === 0) {
            onlineimagename = 'offline_invite_by_IM';
            } else if(customPresence === 1) {
            onlineimagename = 'phone_invite_by_iM';
            } else if(customPresence === 2) {
            onlineimagename = 'busy_invite_by_iM';
            } else if(customPresence === 3) {
            onlineimagename = 'available_invite_by_IM';
            }



            //onlineimagename = online ? 'Status_Available' : 'Status_offline';
            photourl = arguments[i * DATA_REPEAT + 2];
            if(!photourl) {
                photourl = './images/people_icon_b.png';
            }
            html.push('<li class="' + onlinecss + '">');
            html.push('<div class="photo"><img alt="Photo" src="' + photourl + '"></div>');
            html.push('<div class="name">' + htmlEncode(arguments[i * DATA_REPEAT + 1]) + '</div>');

            if(currentLoginType === 'facebook' || currentLoginType === 'google' || currentLoginType === 'zoomus' || currentLoginType === 'sso') {
                html.push('<img class="status" alt="' + onlinetext + '" src="./images/' + onlineimagename + '.png">');
            }

            html.push('<input type="hidden" name="id" value="' + arguments[i * DATA_REPEAT] + '" />');
            html.push('</li>');
        }

        listNode.html(html.join(''));
    };

    window.UpdateMeetingInfo = function (meetingnumber, meetingurl) {
        if(meetingnumber) {
            if(meetingnumber.indexOf('-') === -1) {
                meetingnumber = meetingnumber.substr(0, 3) + '-' + meetingnumber.substr(3, 3) + '-' + meetingnumber.substr(6);
            }
            meetinginfoNode.find('.meetingnumber').text(meetingnumber);
            meetinginfoNode.find('.meetingurl').text(meetingurl);
            meetinginfoNode.show();
        } else {
            meetinginfoNode.hide();
        }

        resetListNodeHeight();
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

    function checkBool(param) {
        if(typeof (param) === 'string') {
            return(param === 'true' || param === '1' || param === 'YES') ? true : false;
        }
        return !!param;
    }

    function findLiNodeByID(id, isTokenNode) {
        var li, container = isTokenNode ? tokenNode : listNode;
        container.find('li ' + hiddenIdSel).each(function () {
            var $this = $(this);
            if($this.val() === id) {
                li = $this.parents('li');
                return false;
            }
        });
        return li;
    }


    function resetListNodeHeight() {
        // body margin: 10 + 10
        // listNode border: 1, listNode padding: 5
        var height = $(window).height();
        height -= titleNode.outerHeight(true);
        height -= tokenNode.outerHeight(true);
        if(meetinginfoNode.is(':visible')) {
            height -= meetinginfoNode.outerHeight(true);
        }
        //height -= 20;
        height -= (1 + 5) * 2;
        listNode.height(height);
    }

    function filterUserList(key) {
        var liNodes = listNode.find('li'),
            key = key.toLowerCase(),
            found = false,
            showAll = false;
        if(lastHoveredUserNode) {
            lastHoveredUserNode.removeClass('hovered');
            lastHoveredUserNode = null;
        }

        if($.trim(key) === '') {
            //liNodes.show();
            //return;
            showAll = true;
        }

        //liNodes.hide();
        liNodes.addClass('hidden');

        var displayUserCount = 0;
        for(var i = 0, count = liNodes.length; i < count; i++) {
            var $this = $(liNodes[i]),
                online = !$this.hasClass('disabled');
            if(showAll) {
                if(online) {
                    displayUserCount++;
                    //$this.show();
                    $this.removeClass('hidden');
                }
            } else {
                if($this.find('.name').text().toLowerCase().indexOf(key) < 0) {
                    //$this.hide();
                } else {
                    displayUserCount++;
                    //$this.show();
                    $this.removeClass('hidden');

                    if(!found && !$this.hasClass('selected')) {
                        $this.addClass('hovered');
                        lastHoveredUserNode = $this;
                        found = true;
                    }

                }
            }

            if(displayUserCount > MAX_USER_COUNT) {
                break;
            }
        }


    }

    function resetTokenInputWidth() {
        var tester = $('#tester');
        tester.css({
            fontSize: inputNode.css("fontSize"),
            fontFamily: inputNode.css("fontFamily"),
            fontWeight: inputNode.css("fontWeight"),
            letterSpacing: inputNode.css("letterSpacing"),
            whiteSpace: "nowrap"
        }).text(inputNode.val());

        inputNode.width(tester.width() + 30);
    }

    function selectUserNode(node) {
        node.removeClass('hovered');
        node.addClass('selected');
        emptyInputNode();

        AddSelectedUser(node.find(hiddenIdSel).val(), node.find('.name').text());
    }

    function emptyInputNode() {
        inputNode.val('');
        filterUserList('');
        resetTokenInputWidth();
    }

    function isSpecialChar(lastChar) {
        if(lastChar === ';' || lastChar === ' ' || lastChar === ',') {
            return true;
        }
        return false;
    }

    function endEdit(val) {
        // Email validate express from: http://codesnippets.joyent.com/posts/show/1917
        var email = val,
            lastChar, emailFilter = /^([a-zA-Z0-9_\.\-])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9]{2,4})+$/;
        if(val.length > 0) {
            lastChar = val.substr(val.length - 1);
        }
        if(isSpecialChar(lastChar)) {
            email = val.substr(0, val.length - 1);
        }

        /* Don't support email.
        if(emailFilter.test(email)) {
            AddSelectedUser(email, email, true);
            emptyInputNode();
        }
		*/
    }

    inputNode.keydown(function (event) {
        var $this = $(this),
            val = $this.val();

        if(val === '' && event.which === 8) {
            RemoveSelectedUser(tokenNode.find('li.token-input-token-facebook:last'), true);
        }

    });

    inputNode.keyup(function (event) {
        var $this = $(this),
            val = $this.val(),
            lastChar = '',
            email;
        if(val.length > 0) {
            lastChar = val.substr(val.length - 1);
        }

        if(event.which === 13) {
            if(lastHoveredUserNode) {
                selectUserNode(lastHoveredUserNode);
                emptyInputNode();
            } else {
                endEdit(val);
            }
            return;
        }

        resetTokenInputWidth();

        if(isSpecialChar(lastChar)) {
            endEdit(val);
        } else {
            filterUserList(val);
        }
    });

    tokenNode.click(function () {
        inputNode.focus();
    });

    tokenNode.delegate('li span.token-input-delete-token-facebook', 'click', function () {
        var $this = $(this),
            li = $this.parents('li'),
            id, customemail;
        id = li.find(hiddenIdSel).val();
        li.remove();

        customemail = li.find(hiddenCustomEmailSel);
        if(!customemail.length) {
            listNode.find('li.selected').each(function () {
                var $this = $(this);
                if($this.find(hiddenIdSel).val() === id) {
                    $this.removeClass('selected');
                    return false;
                }
            });
        }

        resetListNodeHeight();

        if(typeof (CocoaHangoutWindow) !== 'undefined') {
            CocoaHangoutWindow.updateHangoutButton();
        }
    });

    tokenNode.delegate('li', 'hover', function () {
        $(this).toggleClass('hovered');
    });

    listNode.delegate('li', 'click', function () {
        var $this = $(this);
        if($this.hasClass('selected')) {
            $this.removeClass('selected');
            $this.addClass('hovered');

            RemoveSelectedUser($this.find(hiddenIdSel).val(), false);
        } else {
            selectUserNode($this);
        }
    }).delegate('li', 'mouseenter mouseleave', function (event) {
        var $this = $(this);
        if(event.type === 'mouseenter') {
            if(lastHoveredUserNode) {
                lastHoveredUserNode.removeClass('hovered');
            }
            if(!$this.hasClass('selected')) {
                $this.addClass('hovered');
                lastHoveredUserNode = $this;
            }
        } else {
            $this.removeClass('hovered');
            lastHoveredUserNode = null;
        }
    });

    copyButtonNode.click(function () {
        var cocoa = window.CocoaHangoutWindow;
        if(cocoa) {
            cocoa.copyMeetingNumber();
        }
    });

    sendEmailButtonNode.click(function () {
        var cocoa = window.CocoaHangoutWindow;
        if(cocoa) {
            cocoa.sendEmail();
        }
    });


    resetListNodeHeight();

    $(window).resize(function () {
        resetListNodeHeight();
    });

    /*SetLoginType('zoomus');
    UpdateUserList("1", "Hans", "./photo/hans.jpg", "true", 0,
		"2", "Eric Hiname", "./photo/eric.jpg", "true", 1,
		"3", "Read Hiname", "./photo/read.jpg", "true", 1,
		"4", "Flyer Hiname long long long long long", "./photo/flyer.jpg", "false", 2,
		"5", "Sanshi Hiname", "./photo/sanshi.jpg", "true", 2,
		"6", "Read Hiname long long long long long", "./photo/read.jpg", "false", 3,
		"7", "Rico Hiname long long long long long", "./photo/rico.jpg", "false", 3);*/


});
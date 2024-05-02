require([
	'dojo/_base/declare',
	'dijit/layout/ContentPane',
	'dijit/form/TextBox',
	'dijit/form/Textarea',
	'dijit/form/Button',
	'codecompass/model',
	'codecompass/viewHandler'],
function (declare, ContentPane, TextBox, Textarea, Button, model, viewHandler) {
	model.addService('rrservice', 'RRService', RRServiceClient);

	var RR = declare(ContentPane, {
		constructor : function () {
			var self = this;

			this.inputMessageBox = new TextBox({
				id          : 'rr-inputmessagebox',
				trim	    :  true,
				placeHolder : 'Write your GDB command here...',
				onKeyDown   : function(event) {
					if (event.key === 'Enter') {
						event.preventDefault();
						console.log(self.inputMessageBox.value);
						var message = model.rrservice.getMessage(self.inputMessageBox.value);
						console.log(message);
						self.outputMessageArea.set('value', message);
					}
				}
			});

			this.outputMessageArea = new Textarea({
				id           : 'rr-outputmessagearea',
				class	     : 'textArea',
				hovering     : true,
				onMouseEnter : function(event) {
					event.preventDefault();
				}
			});

			this.sendMessageButton = new Button({
				title    : 'Send GDB command',
				id       : 'rr-sendmessagebutton',
				label    : 'Send',
				onClick  : function(event) {
					console.log(self.inputMessageBox.value);
					var message = model.rrservice.getMessage(self.inputMessageBox.value);
				 	console.log(message);
					self.outputMessageArea.set('value', message);
			       		self.inputMessageBox.set('value', ""); 
					self.inputMessageBox.focus();
				}
			});

			this.nextButton = new Button({
				title   : 'Next',
				id      : 'rr-nextbutton',
				label   : 'Next',
				onClick : function(event) {
					var message = model.rrservice.getMessage("next");
					console.log(message);
					self.outputMessageArea.set('value', message);
				}
			});

			this.reverseNextButton = new Button({
				title   : 'Reverse Next',
				id      : 'rr-reversenextbutton',
				label   : 'Reverse Next',
				onClick : function(event) {
					var message = model.rrservice.getMessage("reverse-next");
					console.log(message);
					self.outputMessageArea.set('value', message);
				}
			});

			this.continueButton = new Button({
                                title   : 'Continue',
                                id      : 'rr-continuebutton',
                                label   : 'Continue',
                                onClick : function(event) {
                                        var message = model.rrservice.getMessage("continue");
                                        console.log(message);
                                        self.outputMessageArea.set('value', message);
                                }
                        });

                        this.reverseContinueButton = new Button({
                                title   : 'Reverse Continue',
                                id      : 'rr-reversecontinuebutton',
                                label   : 'Reverse Continue',
                                onClick : function(event) {
                                        var message = model.rrservice.getMessage("reverse-cont");
                                        console.log(message);
                                        self.outputMessageArea.set('value', message);
                                }
                        });

		},

		postCreate : function () {
			this.addChild(this.reverseContinueButton);
			this.addChild(this.reverseNextButton);
			this.addChild(this.nextButton);
			this.addChild(this.continueButton);
			this.addChild(this.inputMessageBox);
			this.addChild(this.sendMessageButton);
			this.addChild(this.outputMessageArea);
		}
	});

	var rr = new RR({
		id    : 'rr',
		title : 'rr debugger'
	});

	viewHandler.registerModule(rr, {
		type : viewHandler.moduleType.Accordion,
		priority : 50
	});

	rr.outputMessageArea.set('value', model.rrservice.startDebugger());
});

require([
	'dojo/_base/declare',
	'dijit/layout/ContentPane',
	'dijit/form/TextBox',
	'dijit/form/Button',
	'codecompass/model',
	'codecompass/viewHandler'],
function (declare, ContentPane, TextBox, Button, model, viewHandler) {
	model.addService('rrservice', 'RRService', RRServiceClient);

	var RR = declare(ContentPane, {
		constructor : function () {
			this.inputMessageBox = new TextBox({
				title       : 'Input Message Box',
				id          : 'rr-inputmessagebox',
				trim	    :  true,
				placeHolder : 'Write your GDB command here...',
				onKeyDown   : function(event) {
					if (event.key === 'Enter') {
						var message = model.rrservice.getMessage('Client: Hi!');
						byId("rr-outputmessagebox").value = message;
					}
				}
			});

			this.outputMessageBox = new TextBox({
				title    : 'Output Message Box',
				id       : 'rr-outputmessagebox',
				trim     :  true,
				readOnly :  true
			});

			this.sendMessageButton = new Button({
				title   : 'Send Message Button',
				id      : 'rr-sendmessagebutton',
				label   : 'Send',
				onClick : function(event) {
					console.log('Button pressed!');
					var message = model.rrservice.getMessage('Client: Hi!');
					outputMessageBox.value = message;
					console.log(message);
					inputMessageBox.value = 'Message sent to server!';
				}
			});
		},

		postCreate : function () {
			this.addChild(this.inputMessageBox);
			this.addChild(this.sendMessageButton);
			this.addChild(this.outputMessageBox);
		}
	});

	var rr = new RR({
		id    : 'rr',
		title : 'rr debugger'
	});

	viewHandler.registerModule(rr, {
		type : viewHandler.moduleType.Accordion,
		priority : 50
	})
});

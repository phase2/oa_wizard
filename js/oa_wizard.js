/**
 * @file
 * Javascript for the OA wizards.
 */

(function ($) {

  Drupal.behaviors.oaWizard = {
    attach: function(context, settings) {
      var $steps = settings.oa_wizard.steps;
      /* $steps is an array of wizard steps.  Each element is an array of key->values
        'title' : The title of the step (shown in header)
        'fields' : An array of field names to be placed in this step
        'help' : The help text for this step
        'showhelp' : TRUE to show help text, false to hide help text
       */
      console.log($steps);
    }
  }

}(jQuery));

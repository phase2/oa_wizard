/**
 * @file
 * Javascript for the OA wizards.
 */

(function ($) {

  Drupal.behaviors.oaWizard = {
    attach: function (context, settings) {
      var $steps = settings.oa_wizard.steps;
      /* $steps is an array of wizard steps.  Each element is an array of key->values
       'title' : The title of the step (shown in header)
       'fields' : An array of field names to be placed in this step
       'help' : The help text for this step
       'showhelp' : TRUE to show help text, false to hide help text
       */
      var $form = $('.node-form');
      $html = "";

      ////
      // Set up HTML Stubs
      ////

      // Set up the Nav Container HTML
      $navItems = $("<ul/>", {
        "class": "nav",
        "role": "tablist",
        html: $("<li/>", {
          html: $("<a/>", {
            "class": "toggle-nav",
            "href": "#",
            click: function (e) {
              e.preventDefault();
              $('#oa-wizard').toggleClass('open');
            }
          }).append(
            $("<span/>", {
              "class": "glyphicon glyphicon-th-list",
            })
            )
        })
      });

      // Set Up the Tab Container HTML
      $tabContent = $("<div/>", {
        "class": "tab-content"
      });

      ////
      // Step Through $steps array
      ////

      $.each($steps, function (key, value) {
        var tab = "",
          fields = value['fields'],
          prevState = (key == 0 ? "disabled" : "enabled"),
          nextState = (key == Object.keys($steps).length - 1 ? "disabled" : "enabled");

        // clean button container
        var $buttons = $("<div/>", {
          "class": "buttons"
        });

        // clean tab container
        $tab = $("<div/>", {
          "class": "tab-pane",
          "id": "tab" + (key + 1),
        });

        ////
        // Append all Navigation Items
        ////

        $("<li/>", {
          html: $("<a/>", {
            "href": "#tab" + (key + 1),
            "role": "tab",
            "data-toggle": "tab",
            text: value['title']
          }).append(
            $("<span/>", {
                "class": "badge",
                text: key + 1
              }
            ))
        }).appendTo($navItems);

        ////
        // Append Fields and buttons to tab content
        ////

        $.each(fields, function (i, field) {
          field = field.replace(/[_]/g, "-");
          if (field == "title") {
            $(".form-item-title").detach().appendTo($tab);
          }
          else {
            $('.field-name-' + field).detach().appendTo($tab);
          }
        });

        // create prev/next buttons
        $prevButton = $("<button/>", {
          "class": "btn btn-primary",
          "type": "button",
          href: "#",
          text: "Previous",
          click: function (e) {
            e.preventDefault;
            $('#oa-wizard [data-toggle="tab"]').eq(key - 1).tab('show');
          }
        }).attr(prevState, "");

        $nextButton = $("<button/>", {
          "class": "btn btn-primary",
          "type": "button",
          href: "#",
          text: "Next",
          click: function (e) {
            e.preventDefault;
            $('#oa-wizard [data-toggle="tab"]').eq(key + 1).tab('show');
          }
        }).attr(nextState, "");

        // Append Buttons
        $buttons.append($prevButton).append($nextButton);

        if (nextState == 'disabled') {
          $('#edit-actions').detach().appendTo($buttons);
        }
        ;

        // place buttons at bottom of tab
        $buttons.appendTo($tab);

        // Add tab to tabContent container
        $tab.appendTo($tabContent);

      });

      ////
      // Put it all together
      ////

      $html = $("<div/>", {
        "class": "",
        "id": "oa-wizard",
        html: $("<div/>", {
          "class": "row",
          html: $navItems
        }).append(
          $('<div/>', {
            "class": "content",
            html: $tabContent
          }))
      });

      ////
      // Hide original form, insert new wizard and show 1st tab
      ////

      $form.find('div').hide();
      $form.prepend($html);
      // show first item
      $('#oa-wizard [data-toggle="tab"]').eq(0).tab('show');
    }
  }

}(jQuery));

